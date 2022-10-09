/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:22:26 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:05:41 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/utils.h"
#include "../include/builtins.h"

//tout ce qui a a voir avec le dossier courant

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
		update_envdir("OLDPWD", get_env_var("PWD", env_list), env_list);
		update_envdir("PWD", new_path, env_list);
		if (ft_strncmp("//", path_cmd, 3) == 0)
			update_envdir("PWD", path_cmd, env_list);
	}
	return (0);
}

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

int	cd(char **cmd, t_env *local_env)
{
	if (str_table_counter(cmd) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (change_dir(cmd[1], local_env) && str_table_counter(cmd) > 1)
	{
		return (1);
	}
	return (0);
}
