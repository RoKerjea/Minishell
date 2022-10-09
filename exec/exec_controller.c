/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:42:18 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 19:07:43 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/common.h"
#include "../include/macro.h"
#include "../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

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

static int	dispatcher_loop(t_list_info *info, t_parsed_cmd *cmd, t_env *env)
{
	while (info->cmd_num < info->size)
	{
		if (info->size == 1 && cmd->exec_type == BUILT)
			return (builtin_main(info, env));
		if (info->size > 1)
			if (pipe(info->pfds) == -1)
				return (EXIT_FAILURE);
		info->cpid[info->cmd_num] = fork();
		if (info->cpid[info->cmd_num] == -1)
			return (close_pfds(info, false), EXIT_FAILURE);
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
	int				res_dispatcher;
	int				last_cmd_status;

	list_info = init_info(cmd_list);
	parsed_cmd = list_info->head;
	list_info->cmd_num = 0;
	res_dispatcher = dispatcher_loop(list_info, parsed_cmd, local_env);
	if (list_info->size == 1 && parsed_cmd->exec_type == BUILT)
		return (destroy_list_info(list_info), res_dispatcher);
	if (res_dispatcher == EXIT_FAILURE)
		return (destroy_list_info(list_info), EXIT_FAILURE);
	close_pfds(list_info, false);
	list_info->status = wait_for_child(list_info->cpid, list_info->size);
	last_cmd_status = list_info->status;
	destroy_list_info (list_info);
	return (exit_status(last_cmd_status));
}
