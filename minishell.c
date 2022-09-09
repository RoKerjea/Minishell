/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/09 17:59:24 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/common.h"
#include "./include/exec.h"
#include "./include/utils.h"
#include "./include/minishell.h"
#include "./include/macro.h"

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

	input = malloc(sizeof(char *) * 2);
	input[1] = 0;
	while (1)
	{
		//input[0] = ft_strdup("cat < Makefile | wc > out2");
		input[0] = readline ("cmd>");//history should use this
		if (input[0] == NULL || input[0][0] == '\0')//J'aime pas :/
		{
			printf("no input!\n");
			continue ;//peux virer les continue si je fais une fonction check input qui fait les deux if avec des returns!!
		}
		add_history (input[0]);
		if (check_input(input[0]) == NO)//can put next steps inside actions of that if?
			continue ;
		//builtin_parser(input, local_env);//ca il faudra le mettre ailleur, mais il marchera pareil
		cmd_list = parser(input[0], local_env);
/* 		printf("\033[1;31m");
		printf ("res at end of parsing =>\n");
		printf("\033[0m");
		print_parsed_list(cmd_list->first); */
/* 		free(input[0]);
		free(input);
		env_destroy_list(local_env); */
		//function that call exec_controller need to create list_info for now, with cmd_list as base
		list_info = cmd_list_info2(cmd_list);
		local_env->lst_exit = exec_controller(list_info, local_env);
		//destroy_final_list(cmd_list);
		//clear history to deal with readline leaks
		//exit (local_env->lst_exit);
		printf("last exit value = %d\n", local_env->lst_exit);
	}
	return (local_env->lst_exit);
}

//start of process, get env and ignore args, make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int		status;
	t_env	*local_env;

	if (!argc || !argv)
		return (0);
	status = 1;
	if (!env[0])
	{
		local_env = minimal_env();
	}
	else
		local_env = env_list(env);
	while (status != 0)
	{
		status = input(local_env);
	}
	return (status);
}
