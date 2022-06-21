/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/21 16:27:11 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	forgelink(t_env_link *prev, t_env_link *now)
{
	prev->next = now;
	now->prev = prev;
}

void	remove_variable(char *str, t_env *env_list)
{
	t_env_link *link;
	t_env_link *linkprev;
	t_env_link *linknext;
	
	link = find_link(str, env_list);
	linkprev = link->prev;
	linknext = link->next;
	if (linknext != NULL && linkprev != NULL)
		forgelink (linkprev, linknext);
	free (link->name);
	free (link->variable);
	free (link);
	env_list->len--;
	if (linkprev == NULL)
	{
		env_list->first = linknext;
		linknext->prev = NULL;
	}
	if (linknext == NULL)
	{
		env_list->last = linkprev;
		linkprev->next = NULL;
	}
}

void	update_variable(char *str, t_env *env_list)
{
	t_env_link *link;
	char	*strvar;
	char	*name;

	strvar = ft_strchr(str, '=');
	name = ft_strndup(str, (strvar - &str[0]));
	link = find_link(name, env_list);
	free (name);
	if (link != NULL)
	{
		free(link->variable);
		link->variable = ft_strdup(&strvar[1]);
	}
	else if (link == NULL)
	{
		link = create_link(str);
		forgelink(env_list->last, link);
		env_list->last = link;
		env_list->len++;
	}
}

char	*get_env_var(char *name, t_env *env_list)
{
	t_env_link	*link;

	link = find_link(name, env_list);
	return(link->variable);
}

t_env_link *find_link(char *var_name, t_env *env_list)
{
	t_env_link	*link;
	unsigned int i;
	
	i = 0;
	link = env_list->first;
	while (i < env_list->len)//probablement pas assez precis
	{
		if (strncmp(var_name, link->name, ft_strlen(var_name)) == 0)
			return (link);
		link = link->next;
		i++;
	}
	return(NULL);
}

void	split_env(char *str, t_env_link *link)
{
	char	*tmp;

	tmp = ft_strchr(str, '=');
	link->name = ft_strndup(str, (tmp - &str[0]));//need ndup!
	if (link->name == NULL)
		return ;
	link->variable = ft_strdup(&tmp[1]);
	if (link->variable == NULL)
		return ;
	return ;
}

//Finish join pls
t_env_link *create_link(char *envstr)
{
	t_env_link *reslink;
	

	reslink = malloc (sizeof(t_env_link));
	split_env(envstr, reslink);
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