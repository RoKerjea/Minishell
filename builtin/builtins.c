/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:06:47 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 17:21:32 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//rajouter une ft par builtin pour verifier input format, return to keep in struct, et printerror
void	builtin_parser(char *cmd, t_env *local_env)
{
	//if (ft_strncmp(cmd, "echo", 4) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))
	if (ft_strncmp(cmd, "exit", 4) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))//need function for exit arg or last exit status
		exit (0);
	if (ft_strncmp(cmd, "env", 3) == 0 && (cmd[3] == ' ' || cmd[3] == '\0'))
		printenv(local_env);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && (cmd[3] == ' ' || cmd[3] == '\0'))
		printpath();
	if (ft_strncmp(cmd, "cd", 2) == 0 && (cmd[2] == ' ' || cmd[2] == '\0'))
		change_dir(cmd, local_env);
	if (ft_strncmp(cmd, "export", 6) == 0 && (cmd[7] != ' ' || cmd[7] != '\0'))
		update_variable(cmd + 6, local_env);//need to trim spaces if there are any, at the begenning
	if (ft_strncmp(cmd, "unset", 5) == 0 && (cmd[6] != ' ' || cmd[6] != '\0'))
		remove_variable(cmd + 5, local_env);
}

//lookup table instead of this /\?
/*
Need to protect in case someone unset a Var before launching minishell or input in minishell
exit//return either arg (exit (arg)) OR exit value of last action
//should be unsigned char (0 -> 255) in any case

unset//should have a return value depending of success O or >0

export//always return (0)

env//always return 0, NO ARGS, NO OPTIONS, but do we ignore or fail?

DIRECTORIES.C
cd//return 0 for success or >0 for error

pwd//always return 0, no option, args cause failure unless spaces

echo//


returns can be tested in real shell with "input && input"!
returns should be between 0 and 255 -> "unsigned char"
*/