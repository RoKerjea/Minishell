/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:08:30 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/29 22:00:54 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/exec.h"
#include "../include/utils.h"
#include "../include/macro.h"

// int	execute(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
// {
// 	int	status;
// 	char	**envp;

// 	envp = make_env_tab(local_env);//to make char **env for execve
// 	status = 0;
// 	if (cmd->exec_type == BUILT)
// 		status = exec_builtin(cmd, local_env);
// 	else
// 		exec_subshell(cmd, info, envp);
// 	return (exit(127), status);
// }

int	exec_subshell(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
{
	int		status;
	char	**envp;

	envp = make_env_tab(local_env);//to make char **env for execve
	status = 0;
	if (info->size > 1)
		exec_pipeline(cmd, info);
	if (exec_redirect(cmd, info))
		exit(EXIT_FAILURE); // handle errno + err_status
	if (cmd->exec_type == BUILT)
		status = exec_builtin(cmd, local_env);
	else
		exec_cmd(cmd->cmd_args, envp);
	if (errno == -1 || errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == EISDIR
		|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
		exit(126);
	return (status);
}
