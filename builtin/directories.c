/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:22:26 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/11 21:24:50 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/utils.h"

void	update_envdir(char *name, char *content, t_env *env_list)
{
	t_env_link	*link;

	link = find_link(name, env_list);
	free (link->variable);
	link->variable = strdup(content);
}

int	change_dir(char *str, t_env *env_list)
{
	char	new_path[PATH_MAX];
	char	*path_cmd;

	if (!str)
		path_cmd = get_env_var("HOME", env_list);
	else
		path_cmd = str;
	if (chdir(path_cmd) != 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		getcwd(new_path, PATH_MAX);
		update_envdir("OLDPWD", get_env_var("PWD", env_list), env_list);//TO FINISH
		update_envdir("PWD", new_path, env_list);
	}
	return (0);
}

void	printpath(void)
{
	char	cur_path[PATH_MAX];

	getcwd(cur_path, PATH_MAX);
	printf("%s\n", cur_path);
}

/*tout ce qui a a voir avec le dossier courant*/