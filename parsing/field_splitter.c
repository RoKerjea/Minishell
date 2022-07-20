/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:35:17 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/20 17:12:58 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	field_counter(char const *s, char c)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i += find_end_quote(s, s[i]);
			continue;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wordcount++;
		i++;
	}
	return (wordcount);
}

int	len_field(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i += find_end_quote(s, s[i]);
			continue;
		}
		i++;
	}
	return (i + 1);
}

char	**field_splitter(char const *s, char c)
{
	char	**res;
	int		wnum;
	int		i;
	int		j;

	res = (char **)malloc(sizeof(char *) * (field_counter(s, c) + 1));
	if (!res)
		return (NULL);
	wnum = 0;
	i = 0;
	while (wnum < field_counter(s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		res[wnum] = malloc(sizeof(char) * (len_field(s + i, c)));
		if (!(res[wnum]))
			return (ft_freetab(res));
		while (s[i] != c && s[i])
			res[wnum][j++] = s[i++];
		res[wnum][j] = '\0';
		wnum++;
	}
	res[wnum] = 0;
	return (res);
}

char **char_tab_fuser(char **str1, char **str2)
{
	char **res;
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (str1[i] != NULL)
		i++;
	while (str1[j] != NULL)
		j++;
	res = malloc (sizeof(char *) * (i + j + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i] != NULL)
	{
		res[i] = str1[i];
		i++;
	}
	while (str2[j] != NULL)
	{
		res[i] = str2[j];
		j++;
		i++;
	}
	res[i] = 0;
	free(str1);
	free(str2);
	return(res);
}
