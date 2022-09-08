/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:17:15 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 14:15:42 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/builtin.h"
#include <stdio.h>

int	exec_builtin(char **cmd, char *const envp[])
{
	int	status;

	(void)envp;
	status = 0;
	if (ft_strncmp(cmd[0], "exit", 4) == 0)
		printf("final_exit() executed.\n");
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
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
		printf("unset() executed.\n");
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
