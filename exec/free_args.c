/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:24:43 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/03 16:24:59 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_err_join(char *path, char *tmp, char **paths)
{
	size_t	i;

	free(tmp);
	free(path);
	i = 0;
	while (paths[i])
		free(paths[i++]);
}

void	free_tab(char **tab)
{
	unsigned int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
