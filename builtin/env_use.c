/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_use.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:10:02 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/03 19:04:44 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILE: everything that use env AFTER it had been created at process startup

//print the env line by line, without formating,
//in the order it was received, with new variables at the bottom
//used for "env" builtin
void	printenv(t_env *env)
{
	int			i;
	t_env_link	*now;

	i = 0;
	now = env->first;
	while (now)
	{
		printf("%s=%s\n", now->name, now->variable);
		now = now->next;
		i++;
	}
}

//delete a variable from env_list, for "unset" builtin
void	remove_variable(char *str, t_env *env_list)
{
	t_env_link	*link;
	t_env_link	*linkprev;
	t_env_link	*linknext;

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

//change content of varable and create it if it doesn't exist yet
//for "export" and "cd" builtins
void	update_variable(char *str, t_env *env_list)
{
	t_env_link	*link;
	char		*strvar;
	char		*name;

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

//find the env_link with the name given in input, and return, it's value in str
//for expand functionality during parsing
char	*get_env_var(char *name, t_env *env_list)
{
	t_env_link	*link;

	link = find_link(name, env_list);
	if (link == NULL)
		return (NULL);
	return (link->variable);
}

//find the env_link with the name given in input, and return the address of the
//link itself, or NULL if there is no var with that name in env
//for env_update, export, expand, cd, pwd, etc
t_env_link	*find_link(char *var_name, t_env *env_list)
{
	t_env_link		*link;

	link = env_list->first;
	while (link != NULL)
	{
		if (strncmp(var_name, link->name, ft_strlen(var_name)) == 0)
			return (link);
		link = link->next;
	}
	return (NULL);
}
