/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/16 22:42:00 by rokerjea         ###   ########.fr       */
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

int global_var = 0;

int	check_input(char *input)
{
	int	len;
	int	i;

	len = strlen(input);
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
		{
			i += find_end_quote(input + i, input[i]);
		}
		if (i > len)
		{
			printf("unclosed quotes!\n");
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
	char		**input;
	t_parsed	*cmd_list;
	t_list_info	*list_info;
	//  int			old_fd;

	input = malloc(sizeof(char *) * 2);
	input[1] = 0;
	input[0] = 0;
	while (1)
	{
		rl_catch_signals = 0;
		rl_outstream = stderr;
		/* input[0] = ft_strdup("exit 25"); */
		//close(0);
		// fd = open("/dev/stdin", O_RDWR);
		// if (fd > 0)
		// 	dup2(fd, 0);
		// old_fd = dup(STDIN_FILENO);
		write(STDERR_FILENO, "minishell >", 11);
		input[0] = readline (" ");//history should use this
		// printf("input[0] = %s\n", input[0]);
		// if (global_var == 130)
		// {
		// 	global_var = 0;
		// 	dup2(old_fd, STDIN_FILENO);
		// 	write(STDERR_FILENO, "\n", 1);
		// 	// old_fd = open("/dev/stdin", O_RDWR);
		// 	continue;
		// }
		rl_outstream = stdout;
		if (input[0] == NULL)
		{
			local_env->lst_exit = 0;
			write(STDERR_FILENO, "exit\n", 5);
			exit(local_env->lst_exit);
		}
		if (input[0][0] == '\0')
			continue;
		// if (input[0] == NULL || input[0][0] == '\0')//J'aime pas :/
		// {
		// 	//global_var = 0
		// 	if (input[0][0] == EOF)
		// 	{
		// 		printf("EOF\n");
		// 		local_env->lst_exit = 130;
		// 	}
		// 	// dup2(old_fd, STDIN_FILENO);
		// 	// write(STDERR_FILENO, "\n", 1);
		// 	continue ;//peux virer les continue si je fais une fonction check input qui fait les deux if avec des returns!!
		// }
		add_history (input[0]);
		if (check_input(input[0]) == NO)//can put next steps inside actions of that if?
			continue ;
		cmd_list = parser(input[0], local_env);
/* 		printf("\033[1;31m");
		printf ("res at end of parsing =>\n");
		printf("\033[0m");
		print_parsed_list(cmd_list->first); */
 		/* free(input[0]);
		free(input); */
		//function that call exec_controller need to create list_info for now, with cmd_list as base
		list_info = cmd_list_info2(cmd_list);
		free (cmd_list);
		local_env->lst_exit = exec_controller(list_info, local_env);
		//destroy_final_list(cmd_list);
		//clear history to deal with readline leaks
		//exit (local_env->lst_exit);
	}
	return (local_env->lst_exit);
}

//start of process, get env and ignore args, make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int					status;
	t_env				*local_env;
	struct sigaction	action;

	if (!argc || !argv)
		return (0);
	if (!env[0])
		local_env = minimal_env();
	else
	{
		sigemptyset(&action.sa_mask);
		action.sa_flags = SA_SIGINFO;
		action.sa_sigaction = signal_handler;
		if (sigaction(SIGUSR2, &action, NULL) == -1)
			dprintf(2, "sigaction error\n");
		//kill(0, SIGUSR2);
		if (sigaction(SIGUSR1, &action, NULL) == -1)
			dprintf(2, "sigaction error\n");

		if (sigaction(SIGINT, &action, NULL) == -1)
			dprintf(2, "sigaction error\n");
		if (sigaction(SIGQUIT, &action, NULL) == -1)
			dprintf(2, "sigaction error\n");
		local_env = env_list(env);
	}
	status = input(local_env);
	return (status);
}
