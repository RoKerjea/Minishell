/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/20 17:47:58 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	forgelink(t_env_link *prev, t_env_link *now)
{
	prev->next = now;
	now->prev = prev;
}

void	update_variable(char *name, char *content, t_env *env_list)
{
	t_env_link *link;

	//parcourir liste until name == link->name
	link = find_link(name, env_list);
	//change link->variable to content
	free(link->variable);
	link->variable = ft_strdup(content);
}

void	new_link(char *newvar, t_env *env_list)
{
	t_env_link	*link;
	t_env_link	*newlink;

	newlink = create_link(newvar);//si la fonction est bien faite, la struct t_env_link est cree et assignee juste avec ca
	link = env_list->last;
	link->next = newlink;
	env_list->last = newlink;
	env_list->len++;
	newlink->prev = link;
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
	
	link = env_list->first;
	while(strncmp(var_name, link->name, ft_strlen(link->name)) != 0)//probablement pas assez precis
	{
		link = link->next;		
	}	
	return(link);
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

split_env(char *str, t_env_link *link)
{
	char	*tmp;

	tmp = ft_strchr('=', str);
	link->name = ft_strndup(str, tmp)//need ndup!
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