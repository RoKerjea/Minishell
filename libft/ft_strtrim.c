/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:53:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/22 13:38:24 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isinstr(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s1[j])
		j++;
	while (ft_isinstr(s1[i], set))
		i++;
	j--;
	while (ft_isinstr(s1[j], set))
		j--;
	if (j <= i)
		res = malloc(sizeof(char) * 1);
	else
	{
		res = malloc(sizeof(char) * (j - i + 1));
		while (i <= j)
			res[k++] = s1[i++];
	}
	res[k] = '\0';
	return (res);
}
