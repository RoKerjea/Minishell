/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:18:56 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:22:10 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"
#include "../include/common.h"
#include "../include/utils.h"
#include <signal.h>

char	*find_free_name(char *str)
{
	int	x;

	x = ft_strlen(str);
	x--;
	str[x] = 'a';
	while (str[x] <= 'z' && access(str, F_OK) == 0)
		str[x]++;
	return (str);
}

char	*findnewname(char *name)
{
	char	*res;
	char	*temp;
	char	*rand;

	rand = malloc(2);
	rand[1] = '\n';
	res = ft_strjoin("/tmp/", name);
	if (!res)
		return (0);
	while (access(res, F_OK) == 0)
	{
		temp = ft_strjoin(res, "a");
		free (res);
		if (!temp)
		{
			free (rand);
			return (0);
		}
		res = find_free_name(temp);
	}
	free (rand);
	return (res);
}
