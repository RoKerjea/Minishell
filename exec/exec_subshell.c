/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:08:30 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 21:40:39 by nvasilev         ###   ########.fr       */
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
	if (!src)
		return (NULL);
	while (src[i] != NULL)
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		res[i] = ft_strdup(src[i]);
		if (!res[i])
			return (ft_freetab(res));
		i++;
	}
	res[i] = NULL;
	return (res);
}

static void	close_pfds_on_error(int pfds[3])
{
	if (pfds[0] > 0)
		close(pfds[0]);
	if (pfds[1] > 0)
		close(pfds[1]);
	if (pfds[2] > 0)
		close(pfds[2]);
}

int	purge_cmd(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
{
	char	**curr_cmd;
	char	**envp;
	int		cpy_pfds[3];

	envp = make_env_tab(local_env);
	env_destroy_list(local_env);
	curr_cmd = str_tab_dup(cmd->cmd_args);
	cpy_pfds[0] = info->pfds[0];
	cpy_pfds[1] = info->pfds[1];
	cpy_pfds[2] = info->pfds[2];
	free(info->cpid);
	free(info);
	destroy_all_cmd(cmd);
	if (!exec_cmd(curr_cmd, envp))
		ft_freetab(curr_cmd);
	close_pfds_on_error(cpy_pfds);
	return (0);
}

void	exec_subshell(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env)
{
	if (info->size > 1)
		exec_pipeline(cmd, info);
	if (exec_redirect(cmd, info))
		return (destroy_list_info(info), env_destroy_list(local_env),
			exit(EXIT_FAILURE));
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
