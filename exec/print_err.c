/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:33:22 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/09 18:35:01 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../include/utils.h"

void	print_err_open(int errnum, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_err(int errnum, char *str, int line)
{
	ft_putstr_fd("minishell ", STDERR_FILENO);
	if (errnum == -1 || errno == ENOENT)
		ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
	else
		ft_putstr_fd("command not found", STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	if (line)
	{
		ft_putstr_fd(":", STDERR_FILENO);
		ft_putnbr_fd(line, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
