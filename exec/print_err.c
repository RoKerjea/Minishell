/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:33:22 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/02 22:38:59 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../include/utils.h"

void	fake_timer(void)
{
	int	i;

	i = 0;
	while (i < 100000000)
		i++;
}

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
	fake_timer();
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (line)
	{
		ft_putnbr_fd(line, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
	}
	if (errnum == -1)
		ft_putstr_fd("command not found", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
