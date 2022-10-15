/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:32:27 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/15 16:14:47 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static int	redir_in_handler(t_parsed_cmd *cmd, t_list_info *info)
{
	info->rfds[P_IN] = open(cmd->redir_in, O_RDONLY);
	if (info->rfds[P_IN] == -1)
		return (print_err_open(errno, cmd->redir_in), EXIT_FAILURE);
	if (dup2(info->rfds[P_IN], STDIN_FILENO) < 0)
		return (print_err_dup(errno), close(info->rfds[P_IN]), EXIT_FAILURE);
	close(info->rfds[P_IN]);
	return (EXIT_SUCCESS);
}

static int	redir_out_handler(t_parsed_cmd *cmd, t_list_info *info)
{
	info->rfds[P_OUT] = open(cmd->redir_out, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (info->rfds[P_OUT] == -1)
		return (print_err_open(errno, cmd->redir_out), EXIT_FAILURE);
	if (dup2(info->rfds[P_OUT], STDOUT_FILENO) < 0)
		return (print_err_dup(errno), close(info->rfds[P_OUT]), EXIT_FAILURE);
	close(info->rfds[P_OUT]);
	return (EXIT_SUCCESS);
}

static int	redir_append_handler(t_parsed_cmd *cmd, t_list_info *info)
{
	info->rfds[P_OUT] = open(cmd->redir_append,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (info->rfds[P_OUT] == -1)
		return (print_err_open(errno, cmd->redir_append), EXIT_FAILURE);
	if (dup2(info->rfds[P_OUT], STDOUT_FILENO) < 0)
		return (print_err_dup(errno), close(info->rfds[P_OUT]), EXIT_FAILURE);
	close(info->rfds[P_OUT]);
	return (EXIT_SUCCESS);
}

static int	redir_heredoc_handler(t_parsed_cmd *cmd, t_list_info *info)
{
	info->rfds[P_IN] = open(cmd->heredoc, O_RDONLY);
	if (info->rfds[P_IN] == -1)
		return (print_err_open(errno, cmd->heredoc), EXIT_FAILURE);
	if (dup2(info->rfds[P_IN], STDIN_FILENO) < 0)
		return (print_err_dup(errno), unlink(cmd->heredoc),
			close(info->rfds[P_IN]), EXIT_FAILURE);
	unlink (cmd->heredoc);
	close(info->rfds[P_IN]);
	return (EXIT_SUCCESS);
}

int	exec_redirect(t_parsed_cmd *cmd_list, t_list_info *list_info)
{
	if (cmd_list->redir_in && ft_strlen(cmd_list->redir_in))
		if (redir_in_handler(cmd_list, list_info))
			return (EXIT_FAILURE);
	if (cmd_list->heredoc && ft_strlen(cmd_list->heredoc))
		if (redir_heredoc_handler(cmd_list, list_info))
			return (EXIT_FAILURE);
	if (cmd_list->redir_out && ft_strlen(cmd_list->redir_out))
		if (redir_out_handler(cmd_list, list_info))
			return (EXIT_FAILURE);
	if (cmd_list->redir_append && ft_strlen(cmd_list->redir_append))
		if (redir_append_handler(cmd_list, list_info))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
