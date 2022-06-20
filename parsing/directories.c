/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:22:26 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/20 17:15:21 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_dir(char *str, t_env *env_list)
{
	char	new_path[PATH_MAX];
	char	*path_cmd;

	if (strlen(str) == 2)
		path_cmd = get_env_var("HOME", env_list);
	else
		path_cmd = str + 3;
	if(chdir(path_cmd) != 0)
	{
		//error message
		printf("error, str = \"%s\"\n", str + 3);
	}
	else
	{
		//update env
		printf("SUCCESS\n");//TO DELETE
		getcwd(new_path, PATH_MAX);
		update_variable("OLDPWD", get_env_var("PWD", env_list), env_list);//TO FINISH
		update_variable("PWD", new_path, env_list);
	}
	return (0);
}

void	printpath(void)
{
	char	cur_path[PATH_MAX];
	
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