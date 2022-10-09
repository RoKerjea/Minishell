/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_use.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:10:02 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 16:47:18 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FILE: everything that use env AFTER it had been created at process startup

char	*join_var_in_str(t_env_link *env_link)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(env_link->name, "=");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, env_link->variable);
	free (temp);
	if (!res)
		return (NULL);
	return (res);
}

char	**make_env_tab(t_env *env)
{
	unsigned int	i;
	char			**res;
	t_env_link		*env_link;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (env->len + 1));
	if (!res)
		return (NULL);
	env_link = env->first;
	while (i < env->len)
	{
		res[i] = join_var_in_str(env_link);
		if (!res[i])
			return (ft_freetab(res));
		env_link = env_link->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

//delete a variable from env_list, for "unset" builtin
void	remove_variable(char *str, t_env *env_list)
{
	t_env_link	*link;
	t_env_link	*linkprev;
	t_env_link	*linknext;

	link = find_link(str, env_list);
	if (link != NULL)
	{
		linkprev = link->prev;
		linknext = link->next;
		forgelink (linkprev, linknext);
		env_destroy_link(link);
		env_list->len--;
		if (linkprev == NULL)
			env_list->first = linknext;
		if (linknext == NULL)
			env_list->last = linkprev;
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
	if (strvar == 0)
		name = ft_strndup (str, ft_strlen(str));
	else
		name = ft_strndup(str, (strvar - &str[0]));
	link = find_link(name, env_list);
	free (name);
	if (link != NULL && strvar != 0)
	{
		free(link->variable);
		link->variable = ft_strdup(&strvar[1]);
	}
	else if (link == NULL)
	{
		link = create_link(str);
		forgelink(env_list->last, link);
		env_list->last = link;
		if (env_list->first == NULL)
			env_list->first = link;
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
