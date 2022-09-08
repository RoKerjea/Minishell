/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:06:43 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 14:53:53 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "../include/utils.h"
#include "../include/exec.h"

static char	*get_path_envp(char *const *env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	**split_path(char *path)
{
	char	**paths;

	if (!path)
	{
		print_err(errno, __FILE__, __LINE__ - 3);
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (!paths)
	{
		free(path);
		print_err(errno, __FILE__, __LINE__ - 3);
		return (NULL);
	}
	return (paths);
}

char	**get_paths(char *const envp[])
{
	char	*path;
	char	**paths;
	char	*tmp;
	size_t	i;

	path = get_path_envp(envp);
	paths = split_path(path);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		if (!paths[i])
		{
			free_err_join(path, tmp, &paths[i + 1]);
			free(paths);
			print_err(errno, __FILE__, __LINE__ - 3);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	free(path);
/*	i = 0;
 	while (paths[i])
	{
		ft_putstr_fd(paths[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	} */
	return (paths);
}
