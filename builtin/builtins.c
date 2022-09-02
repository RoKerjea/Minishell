/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:06:47 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/02 22:27:20 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	str_table_counter(char **str_table)
{
	int	res;
	
	res = 0;
	while (str_table[res] != NULL)
		res++;
	return (res);
}

int	isflag_parser(char *str)//doit etre teste avant chaque str (cmd[x])
{
	if (str[0] == '-')
		return (1);
	return (0);
}

int	isflag_newline(char *str)//doit uniquement etre utilise pour echo, mais avant chaque str(multiples flags possibles)
{
	int	i;

	i = 0;
	while(str[i] == '-')
		i++;
	while(str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	final_exit(char **cmd, t_env *local_env)
{
	int	status;

	status = local_env->lst_exit;
	if (str_table_counter(cmd) > 1)
	{
		status = ft_atoi(cmd[1]);
		if (status == -1)
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			exit (2);
		}
	}
	if (str_table_counter(cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return(1);
	}
	//free all local_env
	printf ("exiting\n");
	exit (status);
}

int	env(char **cmd, t_env *local_env)
{
	if (str_table_counter(cmd) > 1) 
	{
		printf("env: \'%s\': No such file or directory\n", cmd[1]);
		return(127);
	}
	else
		printenv(local_env);
	return(0);
}

int	pwd(char **cmd, t_env *local_env)
{
	(void)cmd;
	(void)local_env;
	printpath();
	return(0);
}

int	cd(char **cmd, t_env *local_env)
{
	if (str_table_counter(cmd) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return(1);
	}
	if (change_dir(cmd[0], local_env) && str_table_counter(cmd) > 1)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		return (2);
	}
	return(0);
}
int	env_export(char **cmd, t_env *local_env)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		update_variable(cmd[i] + 7, local_env);
		i++;
	}
	//NEED print export type for cmd[1] ==NULL
	return (0);
}

int	env_unset(char **cmd, t_env *local_env)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		//printf("str to remove = \'%s\'\n", cmd[i] + 6);
		remove_variable(cmd[i] + 6, local_env);
		i++;
	}
	return (0);
}

//need to present input in compatible way with parsed cmd -> char** with char[0] name of builtin
//rajouter une ft par builtin pour verifier input format, return to keep in struct $?, et printerror
int	builtin_parser(char **cmd, t_env *local_env)
{
	//if (ft_strncmp(cmd, "echo", 4) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))
	if (ft_strncmp(cmd[0], "exit", 4) == 0 && (cmd[0][4] == ' ' || cmd[0][4] == '\0'))//need function for exit arg or last exit status
		return(final_exit(cmd, local_env));
	if (ft_strncmp(cmd[0], "env", 3) == 0 && (cmd[0][3] == ' ' || cmd[0][3] == '\0'))
		return(env(cmd, local_env));
	if (ft_strncmp(cmd[0], "pwd", 3) == 0 && (cmd[0][3] == ' ' || cmd[0][3] == '\0'))
		return(pwd(cmd, local_env));
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && (cmd[0][2] == ' ' || cmd[0][2] == '\0'))
		return(cd(cmd, local_env));
	if (ft_strncmp(cmd[0], "export", 6) == 0 && (cmd[0][7] != ' ' || cmd[0][7] != '\0'))
		return(env_export(cmd, local_env));
	if (ft_strncmp(cmd[0], "unset", 5) == 0 && (cmd[0][6] != ' ' || cmd[0][6] != '\0'))
		return(env_unset(cmd, local_env));
	return (1);
}

/* 
int	echo(char **cmd, t_env *local_env)
{
	int	i;
	int	newline;

	i = 0;
	//parse -n, i++ if
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (newline == 1)
		printf("/n");
	return(0);//protect write?
}*/
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