/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/30 16:18:50 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILE: everything needed to create and assign internal env of minishell
//really need to think about protection from malloc in links!!

int	env_destroy_link(t_env_link *link)
{
	free (link->name);
	free (link->variable);
	free (link);
	return (0);
}

int	env_destroy_list(t_env *env_list)
{
	t_env_link *link;
	t_env_link *nextlink;

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

t_env	*minimal_env(void)
{
	t_env	*env_list;
	char	cur_path[PATH_MAX];
	char	*path;

	env_list = malloc(sizeof(env_list));
	getcwd(cur_path, PATH_MAX);
	env_list->first = create_link("_=/usr/bin/env");
	forgelink(env_list->first, create_link("SHLVL=1"));
	path = ft_strjoin("PWD=", cur_path);
	env_list->last = create_link(path);
	forgelink(env_list->first->next, env_list->last);
	free (path);
	env_list->lst_exit = 0;
	env_list->len = 3;
	return (env_list);
}

//create list, use create_link to assign and create one link by line of env and
//return a struct with variable count and a pointer to the first and last link
t_env	*env_list(char **env)
{
	int			i;
	t_env		*env_list;//maybe need to malloc it actually, bit weird like that!
	t_env_link	*now;
	t_env_link	*prev;


	env_list = malloc(sizeof(t_env));
	i = 0;
	env_list->first = create_link(env[i]);
	i++;
	prev = env_list->first;
	while (env[i])
	{
		now = create_link(env[i]);
		if (prev)
			forgelink(prev, now);
		i++;
		prev = prev->next;
	}
	env_list->len = i;
	env_list->last = now;
	env_list->lst_exit = 0;
	return (env_list);
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

//gerer SHLVL: +1si il existe, = 1 sinon
//utiliser getcwd pour etre sur du pwd actuel
// C'est quoi $_ ???