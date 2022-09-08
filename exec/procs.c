/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:44:36 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 14:16:13 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/exec.h"

void	first_child(t_cmd_list *cmd_list, t_list_info *list_info, char *const envp[], int fd[3])
{
	exec_redirect(cmd_list);
	if (args.infile != -1)
	{
		if (dup2(args.infile, STDIN_FILENO) < 0)
			return (print_err(errno, __FILE__, __LINE__ - 1),
				exit_failure(args, fd, EXIT_FAILURE));
	}
	if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		return (print_err(errno, __FILE__, __LINE__ - 1),
			exit_failure(args, fd, EXIT_FAILURE));

	close(fd[READ_END]);
	close(args.infile);
	exec_cmd(cmd_list->cmd_args, envp);
	return (EXIT_FAILURE); // close everything and free args + exit_status
}

void	inter_children(t_args args, char **cmd, char *const envp[], int fd[3])
{
	if (dup2(fd[TEMP_READ_END], STDIN_FILENO) < 0)
		return (print_err(errno, __FILE__, __LINE__ - 1),
			exit_failure(args, fd, EXIT_FAILURE));
	if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		return (print_err(errno, __FILE__, __LINE__ - 1),
			exit_failure(args, fd, EXIT_FAILURE));
	close(fd[READ_END]);
	exec_cmd(cmd_list->cmd_args, envp);
	return (exit_failure(args, fd, EXIT_FAILURE));
}

void	last_child(t_args args, char **cmd, char *const envp[], int fd[3])
{
	if (dup2(fd[TEMP_READ_END], STDIN_FILENO) < 0)
		return (print_err(errno, __FILE__, __LINE__ - 1),
			exit_failure(args, fd, EXIT_FAILURE));
	if (dup2(args.outfile, STDOUT_FILENO) < 0)
		return (print_err(errno, __FILE__, __LINE__ - 1),
			exit_failure(args, fd, EXIT_FAILURE));
	close(args.outfile);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	exec_cmd(cmd_list->cmd_args, envp);
	if (errno == -1 || errno == ENOENT)
		return (exit_failure(args, fd, 127));
	if (errno == EACCES || errno == EISDIR
		|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
		return (exit_failure(args, fd, 126));
	return (exit_failure(args, fd, EXIT_FAILURE));
}
