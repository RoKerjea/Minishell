/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:22:26 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/20 16:30:39 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
int	change_dir(char *str, t_env *env_list)
{
	char	*new_path[PATH_MAX];
	
	if(chdir(str) != 0)
	{
		//error message
	}
	else
	{
		//update env
		getcwd(new_path, PATH_MAX);
		update_variable("PWD", new_path, env_list);
	}
	return (0);
}*/

void	printpath(void)
{
	char	*cur_path[PATH_MAX];
	
	getcwd(cur_path, PATH_MAX);
	printf("%s\n", cur_path);
}

/*tout ce qui a a voir avec le dossier courant

Builtin

change dir
("./xx", ../xx, /xx, xxx)
int chdir(const char *path);

find new dir
char *getcwd(char *buf, size_t size);
to transform buf in "new full path"

update dir in env
(find dir, edit variable)
update_varibale("PWD", "new full path", env_list)

print dir
(find PWD in env puis print)

*/