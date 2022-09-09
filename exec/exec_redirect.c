/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:32:27 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/09 18:38:05 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/utils.h"
#include "../include/macro.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	exec_redirect(t_parsed_cmd *cmd_list, t_list_info *list_info)
{
	if (cmd_list->redir_in  && ft_strlen(cmd_list->redir_in))
	{
		list_info->rfds[IN] = open(cmd_list->redir_in, O_RDONLY);
		if (list_info->rfds[IN] == -1)
			return (print_err_open(errno, cmd_list->redir_in), EXIT_FAILURE);
		if (dup2(list_info->rfds[IN], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(list_info->rfds[IN]);
	}
	if (cmd_list->redir_out && ft_strlen(cmd_list->redir_out))
	{
		list_info->rfds[OUT] = open(cmd_list->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (list_info->rfds[OUT] == -1)
			return (print_err_open(errno, cmd_list->redir_out), EXIT_FAILURE);
		if (dup2(list_info->rfds[OUT], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(list_info->rfds[OUT]);
	}
	if (cmd_list->redir_append && ft_strlen(cmd_list->redir_append))
	{
		list_info->rfds[OUT] = open(cmd_list->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (list_info->rfds[OUT] == -1)
			return (print_err_open(errno, cmd_list->redir_append), EXIT_FAILURE);
		if (dup2(list_info->rfds[OUT], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(list_info->rfds[OUT]);
	}
	return (EXIT_SUCCESS);
}
