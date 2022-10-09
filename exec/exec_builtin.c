/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:44:29 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 19:58:45 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtins.h"
#include <stdio.h>

int	str_table_counter(char **str_table)
{
	int	res;

	res = 0;
	while (str_table[res] != NULL)
		res++;
	return (res);
}

int	exec_builtin(t_parsed_cmd *cmd, t_env *local_env)
{
	if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
		return (final_exit(cmd, local_env));
	else if (ft_strncmp(cmd->cmd_args[0], "echo", 4) == 0)
		return (echo(cmd->cmd_args, local_env));
	else if (ft_strncmp(cmd->cmd_args[0], "pwd", 3) == 0)
		return (pwd(cmd->cmd_args, local_env));
	else if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0)
		return (cd(cmd->cmd_args, local_env));
	else if (ft_strncmp(cmd->cmd_args[0], "env", 3) == 0)
		return (env(cmd->cmd_args, local_env));
	else if (ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
		return (env_export(cmd->cmd_args, local_env));
	else if (ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0)
		return (env_unset(cmd->cmd_args, local_env));
	return (1);
}

void	is_exit_valid(t_list_info *list_info, t_parsed_cmd *cmd_struct)
{
	char	**cmd;

	cmd = cmd_struct->cmd_args;
	if (str_table_counter(cmd) > 2
		&& (!is_not_num(cmd[1]) || check_overflow(cmd[1]) == 0))
		return ;
	free (list_info->cpid);
	free (list_info);
}

int	builtin_main(t_list_info *list_info, t_env *local_env)
{
	int				exit_status;
	t_parsed_cmd	*cmd_list;
	int				cpy_stdout;

	cmd_list = list_info->head;
	if (ft_strncmp(cmd_list->cmd_args[0], "exit", 4) == 0)
	{
		is_exit_valid(list_info, cmd_list);
		return (final_exit(cmd_list, local_env));
	}
	if (cmd_list->redir_out || cmd_list->redir_append)
		cpy_stdout = dup(STDOUT_FILENO);
	if (exec_redirect(cmd_list, list_info))
		return (EXIT_FAILURE);
	exit_status = exec_builtin(cmd_list, local_env);
	if (cmd_list->redir_out || cmd_list->redir_append)
	{
		dup2(cpy_stdout, STDOUT_FILENO);
		close(cpy_stdout);
	}
	return (exit_status);
}
