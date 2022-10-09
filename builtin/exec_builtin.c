/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:17:15 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 17:07:12 by rokerjea         ###   ########.fr       */
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

void	clean_exit(t_list_info *list_info, t_env *local_env)
{
	t_parsed_cmd	*cmd_list;

	cmd_list = list_info->head;
	free (list_info->cpid);
	free (list_info);
	destroy_all_cmd (cmd_list);
	env_destroy_list(local_env);
	exit(EXIT_FAILURE);
}

int	builtin_main(t_list_info *list_info, t_env *local_env)
{
	int				exit_status;
	t_parsed_cmd	*cmd_list;
	int				cpy_stdout;

	cmd_list = list_info->head;
	if (ft_strncmp(cmd_list->cmd_args[0], "exit", 4) == 0)
		return (final_exit(cmd_list, local_env));
	if (cmd_list->redir_out || cmd_list->redir_append)
		cpy_stdout = dup(STDOUT_FILENO);
	if (exec_redirect(cmd_list, list_info))
		clean_exit (list_info, local_env);
	free (list_info->cpid);
	free (list_info);
	exit_status = exec_builtin(cmd_list, local_env);
	if (cmd_list->redir_out || cmd_list->redir_append)
	{
		dup2(cpy_stdout, STDOUT_FILENO);
		close(cpy_stdout);
	}
	destroy_all_cmd (cmd_list);
	return (exit_status);
}
