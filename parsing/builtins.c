/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:06:47 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/26 19:15:17 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//rajouter une ft par builtin pour verifier input format, return to keep in struct, et printerror
void	builtin_parser(char *input, t_env *local_env)
{
	if (ft_strncmp(input, "exit ", 5) == 0)//need function for exit arg or last exit status
		exit (0);
	if (ft_strncmp(input, "env ", 4) == 0)
		printenv(local_env);
	if (ft_strncmp(input, "pwd ", 4) == 0)
		printpath();
	if (ft_strncmp(input, "cd", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
		change_dir(input, local_env);
	if (ft_strncmp(input, "export", 6) == 0 && (input[6] == ' ' || input[6] != '\0'))
		update_variable(input + 6, local_env);
	if (ft_strncmp(input, "unset", 5) == 0 && (input[5] == ' ' || input[5] != '\0'))
		remove_variable(input + 5, local_env);
}

//lookup table instead of this /\?
/*
exit//return either arg (exit (arg)) OR exit value of last action
//should be unsigned char (0 -> 255) in any case

unset//should have a return value depending of success O or >0

export//always return (0)

env//always return 0, NO ARGS, NO OPTIONS, but do we ignore or fail?

DIRECTORIES.C
cd//return 0 for success or >0 for error

pwd//always return 0, no option, args cause failure unless spaces

echo//


returns can be tested in real shell with "cmd && cmd"!
returns should be between 0 and 255 -> "unsigned char"
*/