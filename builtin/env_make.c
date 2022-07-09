/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/26 18:53:55 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILE: everything needed to create and assign internal env of minishell

//create list, use create_link to assign and create one link by line of env and
//return a struct with variable count and a pointer to the first and last link
t_env	env_list(char **env)
{
	int			i;
	t_env		envlist;//maybe need to malloc it actually, bit weird like that!
	t_env_link	*now;
	t_env_link	*prev;

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

//create single link of env_list, use split_env to assign variables
t_env_link	*create_link(char *envstr)
{
	t_env_link	*reslink;

	reslink = malloc (sizeof(t_env_link));
	split_env(envstr, reslink);
	reslink->next = NULL;
	reslink->prev = NULL;
	return (reslink);
}

//split and assign name and content of variables from env to current link
void	split_env(char *str, t_env_link *link)
{
	char	*tmp;

	tmp = ft_strchr(str, '=');
	link->name = ft_strndup(str, (tmp - &str[0]));
	if (link->name == NULL)
		return ;
	link->variable = ft_strdup(&tmp[1]);
	if (link->variable == NULL)
		return ;
	return ;
}

//link two links to each others
void	forgelink(t_env_link *prev, t_env_link *now)
{
	prev->next = now;
	now->prev = prev;
}

//destroy and free env_list
int	env_destroyer(t_env *env)
{
	t_env_link	*link;
	t_env_link	*nextlink;

	link = env->first;
	while (link != NULL)
	{
		nextlink = link->next;
		free (link->name);
		free (link->variable);
		free (link);
		link = nextlink;
	}
	return (1);
}
