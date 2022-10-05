/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:28:44 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/05 18:53:35 by rokerjea         ###   ########.fr       */
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
#include <stdio.h>

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

void	exec_cmd(char **cmd, char **envp)
{
	ssize_t	i;
	char	*abs_cmd;
	int		ret_access;
	char	**paths;

	i = -1;
	paths = get_paths(envp);
	ret_access = access(cmd[0], F_OK | X_OK | R_OK);
	if (ret_access && !ft_strchr(cmd[0], '/'))
	{
		while (paths[++i] && cmd[0] && errno != -1)
		{
			abs_cmd = ft_strjoin(paths[i], cmd[0]);
			if (!abs_cmd)
				return (print_err(errno, __FILE__, __LINE__ - 2));
			ret_access = access(abs_cmd, F_OK | X_OK | R_OK);
			if (!ret_access && !is_dir(abs_cmd))
				execve(abs_cmd, cmd, envp);//re get path from envp if fail until path[i] == NULL
			free(abs_cmd);
		}
	}
	if (!ret_access && !is_dir(cmd[0]))
		execve(cmd[0], cmd, envp);
	if (!ft_strchr(cmd[0], '/'))
		errno = -1;
	print_err(errno, cmd[0], 0);
}
