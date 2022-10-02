/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:42:18 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/02 23:47:16 by rokerjea         ###   ########.fr       */
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
		{
			if (status == SIGINT)
				write(STDERR_FILENO, "\n", 1);
			if (status == 131)
				write(STDERR_FILENO, "Quit (core dumped)\n", 19);
			last_cmd_status = status;
		}
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

int	exec_controller(t_list_info *list_info, t_env *local_env)
{
	ssize_t			i;
	t_parsed_cmd	*cmd_list;

	cmd_list = list_info->head;
	list_info->cmd_num = 0;
	i = 0;
	while (i < list_info->size)
	{
		if (list_info->size > 1)
			if (pipe(list_info->pfds) == -1)
				return (EXIT_FAILURE); //to protect (free heap + close pfds + errno)
 		if (list_info->size == 1 && cmd_list->exec_type == BUILT)
			return (builtin_main(list_info, local_env));
		list_info->cpid[i] = fork();
		if (list_info->cpid[i] == -1)
			return (EXIT_FAILURE); //to protect (free heap + close pfds + errno)
		if (list_info->cpid[i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			exec_subshell(cmd_list, list_info, local_env);
		}
		cmd_list = cmd_list->next;
		list_info->cmd_num++;
		i++;
		if (list_info->pfds[WRITE_END] > 0)
			close(list_info->pfds[WRITE_END]);
		if (list_info->pfds[TEMP_READ_END] > 0)
			close(list_info->pfds[TEMP_READ_END]);
		list_info->pfds[TEMP_READ_END] = list_info->pfds[READ_END];
	}
	if (list_info->pfds[WRITE_END] > 0)
		close(list_info->pfds[WRITE_END]);
	if (list_info->pfds[TEMP_READ_END] > 0)
		close(list_info->pfds[TEMP_READ_END]);
	if (list_info->pfds[READ_END] > 0)
		close(list_info->pfds[READ_END]);
	list_info->status = wait_for_child(list_info->cpid, list_info->size);
	int end_status = list_info->status;
	destroy_list_info (list_info);
	return (exit_status(end_status));
}

void	destroy_list_info(t_list_info *list_info)
{
	destroy_all_cmd(list_info->head);
	free (list_info->cpid);
	free (list_info);	
}

void	destroy_all_cmd(t_parsed_cmd *cmd)//to use in exec actually
{
	t_parsed_cmd *cmd_next;
	
	while (cmd != NULL)
	{
		cmd_next = cmd->next;
		ft_freetab(cmd->cmd_args);
		if (cmd->redir_in)
			free(cmd->redir_in);
		if (cmd->heredoc)
			free(cmd->heredoc);
		if (cmd->redir_out)
			free(cmd->redir_out);
		if (cmd->redir_append)
			free(cmd->redir_append);
		free (cmd);
		cmd = cmd_next;
	}
	return;
}