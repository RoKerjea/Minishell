/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:47:48 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/18 20:44:37 by rokerjea         ###   ########.fr       */
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
	while (cmd[i] != NULL)
	{
		if (i > 1 && isflag_newline(cmd[i]) == 1)
			ft_putstr_fd("\n", STDOUT_FILENO);
		if (isflag_newline(cmd[i]) == 1)
			newline = 1;
		else
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
		i++;
	}
	if (newline == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
