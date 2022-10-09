/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:08:59 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 21:06:15 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_freetab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (NULL);
	while (tab[i] != NULL)
		i++;
	while (i >= 0)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i--;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}
