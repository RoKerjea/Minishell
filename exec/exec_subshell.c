/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:08:30 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/09 18:35:42 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/exec.h"
#include "../include/utils.h"

void	exec_subshell(t_parsed_cmd *cmd, t_list_info *info, char **envp)
{
	if (info->size > 1)
		exec_pipeline(cmd, info);
	if (exec_redirect(cmd, info))
		exit(EXIT_FAILURE); // handle errno + err_status
	exec_cmd(cmd->cmd_args, envp);
	if (errno == -1 || errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == EISDIR
		|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
		exit(126);
}
