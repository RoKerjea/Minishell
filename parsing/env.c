/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/18 22:49:07 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	forgelink(t_env_link *prev, t_env_link *now)
{
	prev->next = now;
	now->prev = prev;
}

//Finish join pls
t_env_link *create_link(char *envstr)
{
	int i;
	char *tmp;
	char **splistr;
	t_env_link *reslink;
	
	reslink = malloc (sizeof(t_env_link));
	splistr = ft_split(envstr, '=');
	reslink->name = splistr[0];
	//need while to rejoin if multiple '=' in envstr
	reslink->variable = splistr[1];
	i = 2;
	while (splistr[i])
	{
		reslink->variable = ft_strjoin(reslink->variable, "=");
		tmp = ft_strjoin(reslink->variable, splistr[i]);
		free(reslink->variable);
		free(splistr[i]);
		reslink->variable = tmp;
		i++;
	}
	reslink->next = NULL;
	reslink->prev = NULL;
	return (reslink);
}

t_env env_list(char **env)
{
	int i;
	t_env envlist;
	t_env_link *now;
	t_env_link *prev;

	i = 0;
	
	envlist.first = create_link(env[i]);
	i++;
	prev = envlist.first;
	while (env[i])
	{
		now = create_link(env[i]);
		if (prev)
			forgelink(prev, now);
		i++;
		prev = prev->next;
	}
	envlist.len = i;
	envlist.last = now;
	return (envlist);
}