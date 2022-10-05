/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/05 22:07:56 by rokerjea         ###   ########.fr       */
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

	len = strlen(input);
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

void	setup_fds_to_info(t_list_info *info)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		info->pfds[i] = -1;
		info->rfds[i] = -1;
		i++;
	}
	info->pfds[i] = -1;
	info->status = 0;
}

t_list_info	*cmd_list_info2(t_parsed *cmd_list)
{
	t_list_info	*info;

	info = (t_list_info *)malloc(sizeof(t_list_info));
	if (info == NULL)
		return (NULL);
	info->size = cmd_list->len;
	info->head = cmd_list->first;
	info->tail = cmd_list->last;
	free (cmd_list);
	info->cpid = (pid_t *)malloc(sizeof(pid_t) * info->size);
	if (!info->cpid)
	{
		free(info);
		return (NULL);
	}
	setup_fds_to_info(info);
	return (info);
}

char	*read_input(void)
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
	return (input);
}

//start of input loop, should add to history
int	input(t_env *local_env)
{
	char		*input;
	t_parsed	*cmd_list;
	t_list_info	*list_info;

	while (1)
	{
		input = read_input();
		if (errno == EINTR)
			local_env->lst_exit = 128 + SIGINT;
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
		if (cmd_list == NULL)
		{
			local_env->lst_exit = 2;
			continue ;
		}
		if (cmd_list->len == 0)
		{
			if (!(local_env->lst_exit > 128))
				local_env->lst_exit = 0;
			free (cmd_list);
			continue ;
		}
		list_info = cmd_list_info2(cmd_list);
		local_env->lst_exit = exec_controller(list_info, local_env);
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
