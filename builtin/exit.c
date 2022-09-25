/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:49:51 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/24 23:05:39 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/exec.h"
#include "../include/minishell.h"
#include "../include/builtins.h"
#include <stdio.h>

int	is_not_num(char *str)
{
	int		i;
	int		j;
	char	*valid_num;

	valid_num = "+-0123456789";
	i = 0;
	while (str[i])
	{
		j = 0;
		while (valid_num[j] != str[i] && j < 12)
			j++;
		if (j == 12)
			return (1);
		i++;
	}
	return (0);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			i;
	int			min;

	i = 0;
	min = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	res *= min;
	return (res);
}

int	check_overflow(const char *str)
{
	long long	res;
	long long	newres;
	int			i;
	int			min;

	i = 0;
	res = 0;
	min = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			min = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{		
		newres = res * 10;
		if ((newres / 10) != res)
			return (1);
		res = res * 10 + (str[i] - '0') * min;
		if ((res < newres && newres > 0) || (res > newres && newres < 0))
			return (1);
		i++;
	}
	return (0);
}

int	final_exit(t_parsed_cmd *cmd_struct, t_env *local_env)
{
	long long	status;
	char		**cmd;

	cmd = cmd_struct->cmd_args;
	status = local_env->lst_exit;
	if (str_table_counter(cmd) == 2)
	{
		status = ft_atoll(cmd[1]);
		if (is_not_num(cmd[1]) || check_overflow(cmd[1]) == 1)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit (2);
		}
	}
	if (str_table_counter(cmd) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	//free all local_env and cmd_link
	env_destroy_list(local_env);
	ft_freetab(cmd_struct->cmd_args);
	if (cmd_struct->redir_in)
		free(cmd_struct->redir_in);
	if (cmd_struct->heredoc)
		free(cmd_struct->heredoc);
	if (cmd_struct->redir_out)
		free(cmd_struct->redir_out);
	if (cmd_struct->redir_append)
		free(cmd_struct->redir_append);
	free (cmd_struct);
	//rl_clear_histoy
	exit (status % 256);
}
