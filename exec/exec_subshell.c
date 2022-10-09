/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:08:30 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 19:26:16 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/exec.h"
#include "../include/utils.h"
#include "../include/macro.h"
#include "../include/minishell.h"

char	**str_tab_dup(char **src)
{
	char	**res;
	int		i;

	i = 0;
	while (src[i] != NULL)
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		res[i] = ft_strdup(src[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	purge_cmd(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
{
	char	**curr_cmd;
	char	**envp;

	envp = make_env_tab(local_env);
	env_destroy_list(local_env);
	curr_cmd = str_tab_dup(cmd->cmd_args);
	free (info->cpid);
	free (info);
	destroy_all_cmd(cmd);
	exec_cmd(curr_cmd, envp);
	return (0);
}

void	exec_subshell(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
{
	if (info->size > 1)
		exec_pipeline(cmd, info);
	if (exec_redirect(cmd, info))
		exit(EXIT_FAILURE);
	if (cmd->exec_type == BUILT)
		exit(exec_builtin(cmd, local_env));
	else
		purge_cmd(cmd, info, local_env);
	if (errno == -1 || errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == EISDIR
		|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
		exit(126);
}
