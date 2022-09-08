/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:28:44 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 15:23:35 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/exec.h"
#include "../include/utils.h"

int	is_dir(char *path)
{
	int	fd;

	if (!path)
	{
		errno = EINVAL;
		return (errno);
	}
	fd = open(path, O_RDWR);
	if ((fd == -1) && (errno == EISDIR))
	{
		errno = EISDIR;
		return (errno);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

static int	is_null(char *str)
{
	if (!str)
	{
		errno = EINVAL;
		return (errno);
	}
	return (0);
}

void	exec_cmd(char **cmd, char **envp)
{
	ssize_t	i;
	char	*abs_cmd;
	int		ret_access;
	char	**paths;
	
	if (is_null(cmd[0]))
		return (print_err(errno, cmd[0], 0));
	i = -1;
	paths = get_paths(envp);
	while (paths[++i] && cmd[0])
	{
		abs_cmd = ft_strjoin(paths[i], cmd[0]);
		if (!abs_cmd)
			return (print_err(errno, __FILE__, __LINE__ - 2));
		ret_access = access(abs_cmd, F_OK | X_OK);
		if (!ret_access && !is_dir(abs_cmd))
			execve(abs_cmd, cmd, envp);
		free(abs_cmd);
	}
	if (!ft_strchr(cmd[0], '/'))
		errno = -1;
	ret_access = access(cmd[0], F_OK | X_OK);
	if (!ret_access && !is_dir(cmd[0]))
		execve(cmd[0], cmd, envp);
	print_err(errno, cmd[0], 0);
}
