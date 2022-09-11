/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:17:15 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/11 18:09:15 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtin.h"
#include <stdio.h>

int	is_not_num(char *str)
{
	int		i;
	int		j;
	char	*valid_num;

	valid_num = "+-0123456789";
	i = 0;
	while(str[i])
	{
		j = 0;
		while(valid_num[j] != str[i] && j < 12)
			j++;
		if (j == 12)
		return (1);
		i++;
	}
	return (0);
}

typedef struct s_atoll
{
	long long	num;
	int			overflow;
}	t_atoll;

long long	ft_atoll(const char *str)
{
	long long	res;
	int			i;
	int			min;

	i = 0;
	min = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	res *= min;
	return (res);
}

int	check_overflow(const char *str)
{
	long long	res;
	long long	newres;
	int			i;
	int min;
	
	i = 0;
	res = 0;
	min = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{		
		newres = res * 10;
		if ((newres / 10) != res)
		{
			return (1);
		}
		res *= 10;
		newres = res + (str[i] - '0') * min;
		if (newres < res && res > 0)
			return (1);
		if (newres > res && res < 0)
			return (1);
		res += (str[i] - '0') * min;
		i++;		
	}
	return (0);	
}

int	final_exit(t_parsed_cmd *cmd_struct, t_env *local_env)
{
	long long	status;
	char		**cmd;

	cmd = cmd_struct->cmd_args;
	status = local_env->lst_exit;
	if (str_table_counter(cmd) == 2)
	{
		status = ft_atoll(cmd[1]);//need atoll and checker if x > long long max
		if (is_not_num(cmd[1]) || check_overflow(cmd[1]) == 1)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit (2);
		}
	}
	if (str_table_counter(cmd) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return(1);
	}
	//free all local_env and cmd_link
	env_destroy_list(local_env);
	ft_freetab(cmd_struct->cmd_args);
	if (cmd_struct->redir_in)
		free(cmd_struct->redir_in);
	if (cmd_struct->heredoc)
		free(cmd_struct->heredoc);
	if (cmd_struct->redir_out)
		free(cmd_struct->redir_out);
	if (cmd_struct->redir_append)
		free(cmd_struct->redir_append);
	free (cmd_struct);
	exit (status % 256);
}

int	exec_builtin(t_parsed_cmd *cmd, t_env *local_env)
{
	int	status;

	//(void)local_env;
	status = 0;
	if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
		return(final_exit(cmd, local_env));
/* 	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		printf("cd() executed.\n");
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		printf("env() executed.\n");
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		printf("env_export() executed.\n");
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		printf("pwd() executed.\n");
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		printf("echo() executed.\n");
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		printf("unset() executed.\n"); */
	else
		status = 1;
	return (status);
}

// int	exec_builtin(char **cmd, char const *envp[])
// {
// 	int	status;

// 	status = 0;
// 	if (ft_strncmp(cmd[0], "exit", 4) == 0)
// 		status = final_exit(cmd, envp);
// 	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
// 		status = cd(cmd, envp);
// 	else if (ft_strncmp(cmd[0], "env", 3) == 0)
// 		status = env(cmd, envp);
// 	else if (ft_strncmp(cmd[0], "export", 6) == 0)
// 		status = env_export(cmd, envp);
// 	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
// 		status = pwd(cmd, envp);
// 	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
// 		status = echo(cmd, envp);
// 	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
// 		status = env_unset(cmd, envp);
// 	else
// 		status = 1;
// 	return (status);
// }

// int	exec_builtin(char **cmd, t_env *local_env)
// {
// 	int	status;

// 	status = 0;
// 	if (ft_strncmp(cmd[0], "exit", 4) == 0)
// 		status = final_exit(cmd, local_env);
// 	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
// 		status = cd(cmd, local_env);
// 	else if (ft_strncmp(cmd[0], "env", 3) == 0)
// 		status = env(cmd, local_env);
// 	else if (ft_strncmp(cmd[0], "export", 6) == 0)
// 		status = env_export(cmd, local_env);
// 	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
// 		status = pwd(cmd, local_env);
// 	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
// 		status = echo(cmd, local_env);
// 	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
// 		status = env_unset(cmd, local_env);
// 	else
// 		status = 1;
// 	return (status);
// }
