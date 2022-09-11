/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:00:53 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/09 18:39:57 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/exec.h"
#include "../include/utils.h"

void exec_pipeline(t_parsed_cmd *cmd, t_list_info *info)
{
	if ((!cmd->redir_in || !ft_strlen(cmd->redir_in))
		&& (!cmd->redir_append || !ft_strlen(cmd->redir_append))
		&& (!cmd->redir_out || !ft_strlen(cmd->redir_out)))
	{
		 if (dup2(info->pfds[TEMP_READ_END], STDIN_FILENO) < 0)
		 	exit(EXIT_FAILURE);
		if (cmd->next)
		{
			if (dup2(info->pfds[WRITE_END], STDOUT_FILENO) < 0)
				exit(EXIT_FAILURE);
		}
		close(info->pfds[READ_END]);
	}
	else if (cmd->redir_in && ft_strlen(cmd->redir_in))
	{
		if (dup2(info->pfds[WRITE_END], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(info->pfds[READ_END]);
	}
	else if ((cmd->redir_append && ft_strlen(cmd->redir_append))
			|| (cmd->redir_out && ft_strlen(cmd->redir_out)))
	{
		if (dup2(info->pfds[TEMP_READ_END], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(info->pfds[READ_END]);
		close(info->pfds[WRITE_END]);
	}
}