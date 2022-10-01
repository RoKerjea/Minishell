/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:04:12 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/02 00:11:22 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/builtins.h"
#include "../include/common.h"
#include "../include/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_hd_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "^C\n", 3);
	write(STDIN_FILENO, "", 1);
}
