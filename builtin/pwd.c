/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:38:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 19:39:09 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/utils.h"
#include "../include/builtins.h"

void	printpath(t_env *env_list)
{
	char	*cur_path;

	cur_path = get_env_var("PWD", env_list);
	printf("%s\n", cur_path);
}

int	pwd(char **cmd, t_env *local_env)
{
	char	new_path[PATH_MAX];

	(void)cmd;
	if (getcwd(new_path, PATH_MAX) == 0)
		return (1);
	printpath(local_env);
	return (0);
}
