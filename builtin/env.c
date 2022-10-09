/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:59:51 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 16:02:33 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtins.h"
#include <stdio.h>

//print the env line by line, without formating,
//in the order it was received, with new variables at the bottom
//used for "env" builtin
void	printenv(t_env *env)
{
	int			i;
	t_env_link	*now;

	i = 0;
	now = env->first;
	while (now != NULL)
	{
		if (now->variable != NULL)
			printf("%s=%s\n", now->name, now->variable);
		now = now->next;
		i++;
	}
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
