/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:47:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/01 23:52:04 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_destroy_link(t_env_link *link)
{
	free (link->name);
	free (link->variable);
	free (link);
	return (0);
}

int	env_destroy_list(t_env *env_list)
{
	t_env_link	*link;
	t_env_link	*nextlink;

	link = env_list->first;
	while (link != NULL)
	{
		nextlink = link->next;
		env_destroy_link (link);
		link = nextlink;
	}
	free (env_list);
	return (0);
}
