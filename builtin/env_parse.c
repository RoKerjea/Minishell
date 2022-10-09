/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:47:03 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 20:34:13 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//find the env_link with the name given in input, and return the address of the
//link itself, or NULL if there is no var with that name in env
//for env_update, export, expand, cd, pwd, etc
t_env_link	*find_link(char *var_name, t_env *env_list)
{
	t_env_link		*link;

	link = env_list->first;
	while (link != NULL)
	{
		if (ft_strncmp(var_name, link->name, ft_strlen(var_name)) == 0
			&& ft_strncmp(var_name, link->name, ft_strlen(link->name)) == 0)
			return (link);
		link = link->next;
	}
	return (NULL);
}

t_env	*check_env(t_env *env)
{
	t_env_link	*now_link;
	int			fail;

	fail = 0;
	now_link = env->first;
	while (now_link != NULL)
	{
		if (!now_link->name || !now_link->variable)
			fail = 1;
		now_link = now_link->next;
	}
	if (fail == 1)
	{
		env_destroy_list(env);
		return (NULL);
	}
	return (env);
}
