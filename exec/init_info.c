/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:18:45 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 18:19:41 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	setup_fds_to_info(t_list_info *info)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		info->pfds[i] = -1;
		info->rfds[i] = -1;
		i++;
	}
	info->pfds[i] = -1;
	info->status = 0;
}

t_list_info	*init_info(t_parsed *cmd_list)
{
	t_list_info	*info;

	info = (t_list_info *)malloc(sizeof(t_list_info));
	if (info == NULL)
		return (NULL);
	info->size = cmd_list->len;
	info->head = cmd_list->first;
	info->tail = cmd_list->last;
	free (cmd_list);
	info->cpid = (pid_t *)malloc(sizeof(pid_t) * info->size);
	if (!info->cpid)
	{
		free(info);
		return (NULL);
	}
	setup_fds_to_info(info);
	return (info);
}
