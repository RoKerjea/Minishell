/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:53:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/30 18:41:47 by rokerjea         ###   ########.fr       */
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
	int len = j - i + 2;
	if (j <= i)
		res = malloc(sizeof(char) * 1);
	else
	{
		res = malloc(sizeof(char) * (j - i + 2));
		while (i <= j)
			res[k++] = s1[i++];
	}
	res[k] = '\0';
	if (res[k] == '\0')
	{
		printf ("string 0 terminated corrrectly!\n");
		printf("last char = (%c)\n", res[k - 1]);
	}
	printf("res after trim = \"%s\", len = %i\n", res, len);
	return (res);
}
