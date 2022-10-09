/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:42:18 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 17:42:38 by nvasilev         ###   ########.fr       */
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
#include <stdbool.h>

int	wait_for_child(pid_t *cpid, unsigned int max_proc)
{
	ssize_t	i;
	int		status;
	int		last_cmd_status;

	i = 0;
	status = 0;
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
	return (status);
}

void	setup_fds_to_info(t_list_info *info)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		info->pfds[i] = -1;
		info->rfds[i] = -1;
		i++;
	}
	info->pfds[i] = -1;
	info->status = 0;
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
	free (cmd_list);
	info->cpid = (pid_t *)malloc(sizeof(pid_t) * info->size);
	if (!info->cpid)
	{
		free(info);
		return (NULL);
	}
	setup_fds_to_info(info);
	return (info);
}

static void	close_pfds(t_list_info *info, bool is_in_loop)
{
	if (info->pfds[WRITE_END] > 0)
		close(info->pfds[WRITE_END]);
	if (info->pfds[TEMP_READ_END] > 0)
		close(info->pfds[TEMP_READ_END]);
	if (!is_in_loop)
		if (info->pfds[READ_END] > 0)
			close(info->pfds[READ_END]);
}

static int	dispatcher_loop(t_list_info *info, t_parsed_cmd *cmd, t_env *env, int *is_single_builtin)
{
	while (info->cmd_num < info->size)
	{
		if (info->size == 1 && cmd->exec_type == BUILT)
		{
			*is_single_builtin = 1;
			return (builtin_main(info, env));
		}
		if (info->size > 1)
			if (pipe(info->pfds) == -1)
				return (EXIT_FAILURE);
		info->cpid[info->cmd_num] = fork();
		if (info->cpid[info->cmd_num] == -1)
			return (EXIT_FAILURE);
		if (info->cpid[info->cmd_num] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			exec_subshell(cmd, info, env);
		}
		cmd = cmd->next;
		info->cmd_num++;
		close_pfds(info, true);
		info->pfds[TEMP_READ_END] = info->pfds[READ_END];
	}
	return (EXIT_SUCCESS);
}

int	exec_controller(t_parsed *cmd_list, t_env *local_env)
{
	t_list_info		*list_info;
	t_parsed_cmd	*parsed_cmd;
	int				is_single_builtin;
	int				res_dispatcher;
	int				last_cmd_status;

	list_info = cmd_list_info2(cmd_list);
	parsed_cmd = list_info->head;
	is_single_builtin = 0;
	list_info->cmd_num = 0;
	res_dispatcher = dispatcher_loop(list_info, parsed_cmd, local_env, &is_single_builtin);
	if (is_single_builtin)
	{
		destroy_list_info(list_info);
		return (res_dispatcher);
	}
	close_pfds(list_info, false);
	list_info->status = wait_for_child(list_info->cpid, list_info->size);
	last_cmd_status = list_info->status;
	destroy_list_info (list_info);
	return (exit_status(last_cmd_status));
}

void	destroy_list_info(t_list_info *list_info)
{
	destroy_all_cmd(list_info->head);
	free (list_info->cpid);
	free (list_info);
}

void	destroy_all_cmd(t_parsed_cmd *cmd)
{
	t_parsed_cmd	*cmd_next;

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
}
