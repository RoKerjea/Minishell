/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:06:47 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/17 19:33:11 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//need to present input in compatible way with parsed cmd -> char** with char[0] name of builtin
//rajouter une ft par builtin pour verifier input format, return to keep in struct $?, et printerror
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
		update_variable(cmd + 6, local_env);//need to trim spaces if there are any, at the beginning
	if (ft_strncmp(cmd, "unset", 5) == 0 && (cmd[6] != ' ' || cmd[6] != '\0'))
		remove_variable(cmd + 5, local_env);
}
/*
int	final_exit(char *cmd, t_env *local_env)
{
	//if too many words, "bash: exit: too many arguments" and return to prompt
	//if not a num : "bash: exit: (cmd): numeric argument required" and exit(0) ou ($_)
	//free all local_env
	//if cmd contain num after exit:
	//exit(atoi(cmd + 4));
	//else
		exit (local_env->last_exit);
}

int	env(char *cmd, t_env *local_env)
{
	//if env cmd : "env: ‘cmd’: No such file or directory" and return(X)
	//else printenv(local_env); and return(0)
}

int	echo(char *cmd, t_env *local_env)
{
	//parse -n
	//printf("%s", cmd + 5);
	//printf("/n") if no -n
	//return(0)
}

int	pwd(char *cmd, t_env *local_env)
{
	printpath();
	return(0);
}

int	cd(char *cmd, t_env *local_env)
{
	if (change_dir(cmd, local_env))
		//probleme, return (2);
	return(0);
}

int	export(char *cmd, t_env *local_env)
{}

int	unset(char *cmd, t_env *local_env)
{}
 */
/*
need to return int for exit status, to be used for "$?"
all of them should use(char *cmd, t_env *local_env)
//lookup table instead of this /\?
//function pointer could be used because all builtins return an int and use a char* as an input1
//(what about env?? it IS used or useful in nearly all cases, possibly to be fused with $? for exit too)

Need to protect CD and PWD in case someone unset a Var before launching minishell or input in minishell
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