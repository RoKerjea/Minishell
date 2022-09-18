/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:04:12 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/18 17:47:34 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/builtins.h"
#include "../include/common.h"
#include "../include/minishell.h"

void	signal_handler(int signo, siginfo_t *siginfo, void *ucontext)
{
	static int		is_interactive = 1;
	static pid_t	pid = 0;

	(void)ucontext;
	if (signo == SIGUSR1 && siginfo->si_pid == pid)
	{
		if (is_interactive == 0)
			is_interactive = 1;
		else
			is_interactive = 0;
	}
	if (signo == SIGUSR2 && pid == 0)
		pid = siginfo->si_pid;
	if (is_interactive == 1)
	{
		if (signo == SIGINT)
		{
			// close(STDIN_FILENO);
			// rl_on_new_line();
			// rl_on_new_line();
			write(STDERR_FILENO, "^C", 2);
			rl_replace_line("", 0);
			write(STDERR_FILENO, "\nminishell >", 12);
			rl_on_new_line();
			// write(STDERR_FILENO, "\ncmd >", 6);
			// rl_redisplay();
			// rl_on_new_line();
			// rl_on_new_line();
			// rl_on_new_line();
			// rl_redisplay();
			// global_var = 130;
		}
		// if (signo == SIGQUIT)
			// write(STDERR_FILENO, "\b\b  \b\b", 6);
	}
	else
	{
		if (signo == SIGINT)
			write(1, "SIGINT non interactive\n", 23);
		if (signo == SIGQUIT)
			write(1, "SIGQUIT non interactive\n", 24);
	}
}
