/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:08:59 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/30 17:44:28 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	while (i >= 0)
	{
		if (tab[i])
			free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}
