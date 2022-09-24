/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:17:15 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/24 20:16:33 by rokerjea         ###   ########.fr       */
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

int	env(char **cmd, t_env *local_env)
{
	if (str_table_counter(cmd) > 1)
	{
		ft_putstr_fd("env: \'", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd("\': No such file or directory\n", STDERR_FILENO);
		return (125);
	}
	else
		printenv(local_env);
	return (0);
}

int	pwd(char **cmd, t_env *local_env)
{
	(void)cmd;
	(void)local_env;
	printpath();
	return (0);
}

int	cd(char **cmd, t_env *local_env)
{
	if (str_table_counter(cmd) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (change_dir(cmd[1], local_env) && str_table_counter(cmd) > 1)
	{
		return (1);
	}
	return (0);
}

int	env_unset(char **cmd, t_env *local_env)
{
	int	i;

	i = 1;
	while (cmd[i] != NULL)
	{
		remove_variable(cmd[i], local_env);
		i++;
	}
	return (0);
}

void	print_export(t_env *local_env)
{
	t_env_link	*now;

	now = local_env->first;
	while (now)
	{
		printf("declare -x %s=\"%s\"\n", now->name, now->variable);
		now = now->next;
	}
}

int	env_export(char **cmd, t_env *local_env)
{
	int	i;

	i = 1;
	while (cmd[i] != NULL)
	{
		update_variable(cmd[i], local_env);
		i++;
	}
	if (cmd[i] == NULL)
		print_export(local_env);
	return (0);
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
