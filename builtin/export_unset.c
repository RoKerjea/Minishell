/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:06:50 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:07:57 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtins.h"

int	env_unset(char **cmd, t_env *local_env)
{
	int	i;

	i = 1;
	while (cmd[i] != NULL)
	{
		remove_variable(cmd[i], local_env);
		i++;
	}
	return (0);
}

void	print_export(t_env *local_env)
{
	t_env_link	*now;

	now = local_env->first;
	while (now)
	{
		printf("declare -x %s=\"%s\"\n", now->name, now->variable);
		now = now->next;
	}
}

int	env_export(char **cmd, t_env *local_env)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		print_export(local_env);
	while (cmd[i] != NULL)
	{
		update_variable(cmd[i], local_env);
		i++;
	}
	return (0);
}
