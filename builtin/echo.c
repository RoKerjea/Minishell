/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:47:48 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/29 18:02:45 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtins.h"
#include <stdio.h>

//doit uniquement etre utilise pour echo
int	isflag_newline(char *str)
{
	//printf("Checking str \'%s\'\n", str);
	int	i;

	i = 0;
	if (!str || str == NULL)
		return (0);
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0' || str[i - 1] != 'n')
		return (0);
	return (1);
}

int	echo(char **cmd, t_env *local_env)
{
	int	i;
	int	newline;

	(void)local_env;
	i = 1;
	newline = 0;
	while (isflag_newline(cmd[i]) == 1)
	{
		//printf ("str %s est un -n\n", cmd[i]);
		newline = 1;
		i++;
	}
	while (cmd[i] != NULL)
	{		
	/* 	if (isflag_newline(cmd[i]) == 1)
			newline = 1;
		else */
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
