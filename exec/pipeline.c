/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:30:09 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 14:16:08 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_pipeline(t_cmd_list *cmd_list, char const *envp[])
{
	ssize_t		i;
	int			status;
	t_list_info	list_info;
	int			fd[3];

	init_tab(fd, 3);
	list_info = cmd_list_info(cmd_list);
	return (status);
}
