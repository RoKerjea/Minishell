/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:38:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 12:09:03 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/utils.h"
#include "../include/builtins.h"

void	printpath(t_env *env_list)
{
	char	*cur_path;

	cur_path = get_env_var("PWD", env_list);
	ft_putstr_fd(cur_path, 1);
	ft_putstr_fd("\n", 1);
}

int	pwd(char **cmd, t_env *local_env)
{
	(void)cmd;
	printpath(local_env);
	return (0);
}
