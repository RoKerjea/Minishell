/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:42:18 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/15 18:27:08 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/common.h"
#include "../include/macro.h"
#include "../include/minishell.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int	wait_for_child(pid_t *cpid, unsigned int max_proc)
{
	ssize_t	i;
	int		status;
	int		last_cmd_status;

	i = 0;
	while (i < max_proc)
	{
		waitpid(cpid[i], &status, 0);
		if (cpid[i] == cpid[max_proc - 1])
			last_cmd_status = status;
		i++;
	}
	return (last_cmd_status);
}

int	exit_status(int status)
{
	if (errno == -1 || errno == ENOENT)
		return (127);
	if (errno == EACCES || errno == EISDIR
		|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
		return (126);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	execute(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
{
	int	status;
	char	**envp;

	envp = make_env_tab(local_env);//to make char **env for execve
	status = 0;
	if (cmd->exec_type == BUILT)
		status = exec_builtin(cmd, local_env);
	else
		exec_subshell(cmd, info, envp);
	return (exit(status), status);
}

int	exec_controller(t_list_info *list_info, t_env *local_env)
{
	ssize_t		i;
	t_parsed_cmd	*cmd_list;

	i = 0;
	cmd_list = list_info->head;
	kill(0, SIGUSR1);
	while (i < list_info->size)
	{
		if (list_info->size > 1)
			if (pipe(list_info->pfds) == -1)
				return (EXIT_FAILURE); //to protect (free heap + close pfds + errno)
 		if (list_info->size == 1 && cmd_list->exec_type == BUILT)
		{
			list_info->status = exec_builtin(cmd_list, local_env);
			break;
		}
		list_info->cpid[i] = fork();
		if (list_info->cpid[i] == -1)
			return (EXIT_FAILURE); //to protect (free heap + close pfds + errno)
		if (list_info->cpid[i] == 0)
			list_info->status = execute(cmd_list, list_info, local_env);
		cmd_list = cmd_list->next;
		i++;
		close(list_info->pfds[WRITE_END]);
		if (list_info->pfds[TEMP_READ_END] > 0)
			close(list_info->pfds[TEMP_READ_END]);
		list_info->pfds[TEMP_READ_END] = list_info->pfds[READ_END];
	}
	close(list_info->pfds[WRITE_END]);
	if (list_info->pfds[TEMP_READ_END] > 0)
		close(list_info->pfds[TEMP_READ_END]);
	close(list_info->pfds[READ_END]);
	list_info->status = wait_for_child(list_info->cpid, list_info->size);
	kill(0, SIGUSR1);
	return (exit_status(list_info->status));
}
