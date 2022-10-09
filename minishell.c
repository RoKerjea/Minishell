/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 20:31:12 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/common.h"
#include "./include/exec.h"
#include "./include/utils.h"
#include "./include/minishell.h"
#include "./include/macro.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	check_input(char *input)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
			i += find_end_quote(input + i, input[i]) - 1;
		if (i > len + 1)
		{
			write(2, "unclosed quotes!\n", 17);
			return (NO);
		}
		i++;
	}
	return (YES);
}

char	*read_input(t_env *local_env)
{
	char	*input;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	input = readline ("minishell$ ");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stdout;
	if (errno == EINTR)
		local_env->lst_exit = 128 + SIGINT;
	return (input);
}

int	check_valid_cmd(t_parsed *cmd_list, t_env *local_env)
{
	if (cmd_list == NULL)
	{
		local_env->lst_exit = 2;
		return (NO);
	}
	if (cmd_list->len == 0)
	{
		if (!(local_env->lst_exit > 128))
			local_env->lst_exit = 0;
		free (cmd_list);
		return (NO);
	}
	return (YES);
}

//start of input loop, should add to history
int	input(t_env *local_env)
{
	char		*input;
	t_parsed	*cmd_list;

	while (1)
	{
		input = read_input(local_env);
		if (input == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			free(input);
			exit(env_destroy_list (local_env));
		}
		if (input[0] == '\0' || is_only_space(input) || !check_input(input))
		{
			free(input);
			continue ;
		}
		add_history (input);
		cmd_list = parser(input, local_env);
		free(input);
		if (check_valid_cmd(cmd_list, local_env) == NO)
			continue ;
		local_env->lst_exit = exec_controller(cmd_list, local_env);
	}
	return (local_env->lst_exit);
}

//start of process, get env and ignore args
//make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int					status;
	t_env				*local_env;

	if (!argc || !argv)
		return (0);
	if (!env || !env[0])
		local_env = minimal_env();
	else
		local_env = env_list(env);
	if (!local_env)
		return (0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = input(local_env);
	return (status);
}
