/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/02 18:07:50 by rokerjea         ###   ########.fr       */
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
	info->cpid = NULL;
	info->cpid = (pid_t *)malloc(sizeof(pid_t) * info->size);
	if (!info->cpid)
	{
		free(info);
		return (NULL);
	}
	for (size_t i = 0; i < 3; i++)
		info->pfds[i] = -1;
	for (size_t i = 0; i < 2; i++)
		info->rfds[i] = -1;
	info->status = 0;
	return (info);
}

//start of input loop, should add to history, tokenize->parse->expand->send to exec
int	input(t_env *local_env)
{
	char		*input;
	t_parsed	*cmd_list;
	t_list_info	*list_info;

	while (1)
	{
		rl_catch_signals = 0;
		rl_outstream = stderr;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline ("minishell$ ");//history should use this
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		rl_outstream = stdout;
		if (errno == EINTR)
			local_env->lst_exit = 128 + SIGINT;
		if (input == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			//rl_clear_history ??
			//destroy env and free input here? need function anyway
			exit(local_env->lst_exit);
		}
		if (input[0] == '\0' || is_only_space(input))
			continue;
		add_history (input);
		if (check_input(input) == NO)//can put next steps inside actions of that if?
			continue ;
		cmd_list = parser(input, local_env);
		if (cmd_list == NULL)
		{
			local_env->lst_exit = 2;//source de status = 2 instead of 1 for some errors
			continue;
		}
		if (cmd_list->len == 0)
		{
			local_env->lst_exit = 0;
			free (cmd_list);
			continue;
		}
		free(input);
		//function that call exec_controller need to create list_info for now, with cmd_list as base
		list_info = cmd_list_info2(cmd_list);
		//free (cmd_list);
		local_env->lst_exit = exec_controller(list_info, local_env);
		//destroy_final_list(cmd_list);
		//clear history to deal with readline leaks
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
	if (!env[0])
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
