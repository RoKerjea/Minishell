/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/02 19:34:55 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILE: everything needed to create and assign internal env of minishell
//really need to think about protection from malloc in links!!

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

t_env	*minimal_env(void)
{
	t_env		*env_list;
	char		cur_path[PATH_MAX];
	char		*path;
	t_env_link	*temp;

	env_list = malloc(sizeof(env_list));
	if (!env_list)
		return (NULL);
	getcwd(cur_path, PATH_MAX);
	env_list->first = create_link("_=/usr/bin/env");
	forgelink(env_list->first, create_link("SHLVL=1"));
	path = ft_strjoin("PWD=", cur_path);
	env_list->last = create_link(path);
	forgelink(env_list->first->next, env_list->last);
	free (path);
	path = ft_strjoin("PATH=",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	temp = create_link(path);
	free (path);
	forgelink(env_list->last, temp);
	env_list->last = temp;
	env_list->lst_exit = 0;
	env_list->len = 4;
	return (check_env(env_list));
}

//create list, use create_link to assign and create one link by line of env and
//return a struct with variable count and a pointer to the first and last link
t_env	*env_list(char **env)//need protection
{
	int			i;
	t_env		*env_list;
	t_env_link	*now;
	t_env_link	*prev;

	env_list = malloc(sizeof(t_env));
	if (!env_list)
		return (NULL);
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
	update_shlvl(env_list);
	return (check_env(env_list));
}

void	update_shlvl(t_env *local_env)
{
	char	*level;
	char	*newlevel;
	int		lvl;

	level = get_env_var("SHLVL", local_env);
	lvl = ft_atoi(level);
	lvl++;
	level = ft_itoa(lvl);
	newlevel = ft_strjoin("SHLVL=", level);
	update_variable(newlevel, local_env);
	free (level);
	free (newlevel);
}

//split and assign name and content of variables from env to current link
t_env_link	*create_link(char *envstr)
{
	char		*tmp;
	t_env_link	*reslink;

	if (!envstr)
		return (NULL);
	reslink = memset_alloc(0, sizeof(t_env_link));
	if (!reslink)
		return (NULL);
	tmp = ft_strchr(envstr, '=');
	if (tmp == 0)
		reslink->name = ft_strdup(envstr);
	else
	{	
		reslink->name = ft_strndup(envstr, (tmp - &envstr[0]));
		reslink->variable = ft_strdup(&tmp[1]);
	}
	return (reslink);
}

//bond two links to each others
void	forgelink(t_env_link *prev, t_env_link *now)
{
	prev->next = now;
	now->prev = prev;
}
