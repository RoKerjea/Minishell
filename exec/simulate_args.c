/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:21:42 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 14:27:07 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/common.h"
#include "../include/exec.h"
#include "../include/macro.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

t_parsed_cmd	*cmd_list_create(int type, char **args, char *in, char *out, char *append, char *hd)
{
	t_parsed_cmd	*new;

	new = (t_parsed_cmd *)malloc(sizeof(t_parsed_cmd));
	if (new == NULL)
		return (NULL);
	new->exec_type = type;
	new->cmd_args = args;
	new->redir_in = in;
	new->redir_out = out;
	new->redir_append = append;
	new->heredoc = hd;
	new->next = NULL;
	return (new);
}

void		cmd_list_push_back(t_parsed_cmd **list, t_parsed_cmd *new)
{
	t_parsed_cmd	*tmp;

	tmp = *list;
	if (tmp == NULL)
	{
		*list = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
/*
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
}*/

t_list_info	*cmd_list_info(t_parsed_cmd *cmd_list)
{
	t_list_info	*info;

	info = (t_list_info *)malloc(sizeof(t_list_info));
	if (info == NULL)
		return (NULL);
	info->size = 0;
	info->head = NULL;
	info->tail = NULL;
	info->cpid = NULL;
	while (cmd_list)
	{
		info->size++;
		if (info->head == NULL)
		{
			info->head = cmd_list;
			info->tail = cmd_list;
		}
		else
			info->tail = cmd_list;
		cmd_list = cmd_list->next;
	}
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

void	print_cmd_list(t_parsed_cmd *cmd_list)
{
	size_t	i;

	while (cmd_list)
	{
		if (cmd_list->exec_type == BUILT)
			printf("type: BUILTIN\n");
		else
			printf("type: CMD\n");
		i = 0;
		printf("command: ");
		while (cmd_list->cmd_args[i])
		{
			printf("%s ", cmd_list->cmd_args[i]);
			i++;
		}
		printf("\nredir_in: %s\n", cmd_list->redir_in);
		printf("redir_out: %s\n", cmd_list->redir_out);
		printf("redir_append: %s\n", cmd_list->redir_append);
		printf("heredoc: %s\n", cmd_list->heredoc);
		cmd_list = cmd_list->next;
	}
}

t_parsed_cmd	*create_pipeline(int argc, char *argv[], char *const envp[])
{
	t_parsed_cmd	*cmd_list;
	t_parsed_cmd	*tmp;

	(void)envp;
	cmd_list = NULL;
	tmp = NULL;
	while (argc > 1)
	{
		tmp = cmd_list_create(atoi(argv[1]), ft_split(argv[2], ' '), argv[3], argv[4], argv[5], argv[6]);
		if (tmp == NULL)
			return (NULL);
		cmd_list_push_back(&cmd_list, tmp);
		argc -= 6;
		argv += 6;
	}
	return (cmd_list);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmd_list(t_parsed_cmd *cmd_list)
{
	t_parsed_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_array(tmp->cmd_args);
		free(tmp);
	}
}
