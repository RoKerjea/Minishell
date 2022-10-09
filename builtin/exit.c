/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:49:51 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 15:24:04 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtins.h"
#include <stdio.h>

void	exit_error(char **cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	final_exit(t_parsed_cmd *cmd_struct, t_env *local_env)
{
	long long	status;
	char		**cmd;

	cmd = cmd_struct->cmd_args;
	status = local_env->lst_exit;
	if (str_table_counter(cmd) >= 2)
	{
		status = ft_atoll(cmd[1]);
		if (is_not_num(cmd[1]) || check_overflow(cmd[1]) == 1)
		{
			exit_error(cmd);
			env_destroy_list(local_env);
			destroy_all_cmd(cmd_struct);
			exit (2);
		}
	}
	if (str_table_counter(cmd) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	env_destroy_list(local_env);
	destroy_all_cmd(cmd_struct);
	exit (status % 256);
}

/* void	destroy_cmd_link(t_parsed_cmd *link)
{
	if (link->cmd_args)
		ft_freetab(link->cmd_args);
	if (link->redir_in)
		free(link->redir_in);
	if (link->heredoc)
		free(link->heredoc);
	if (link->redir_out)
		free(link->redir_out);
	if (link->redir_append)
		free(link->redir_append);
	free (link);
} */
