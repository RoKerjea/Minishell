/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:47:48 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/21 00:10:40 by rokerjea         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	if (str[0] != '-')
		return (0);
	while (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
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
	while (cmd[i] != NULL && cmd[i][0] != '\0')
	{		
		if (isflag_newline(cmd[i]) == 1)
			newline = 1;
		else
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
		 if (isflag_newline(cmd[i]) != 1 && (isflag_newline(cmd[i + 1]) != 1 && cmd[i + 1] != NULL))
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
