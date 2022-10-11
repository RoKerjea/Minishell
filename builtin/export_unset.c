/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:06:50 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 13:48:09 by rokerjea         ###   ########.fr       */
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

void	print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
}

int	check_export_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) == 1)
	{
		print_export_error (str);
		return (0);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			print_export_error (str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	env_export(char **cmd, t_env *local_env)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		print_export(local_env);
	while (cmd[i] != NULL)
	{
		if (check_export_name(cmd[i]) == 0)
			return (1);
		update_variable(cmd[i], local_env);
		i++;
	}
	return (0);
}

/*RULES

cant start by number
can contain alphanumeric char
can contain '_'
*/