/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:12:08 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:14:18 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/macro.h"
#include "../include/utils.h"

int	field_counter(char *s, char c)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i += find_end_quote(s + i, s[i]);
			if (s[i] == c || s[i] == '\0')
				wordcount++;
		}
		else if ((s[i] != c && s[i] != '\'' && s[i] != '\"' && (s[i + 1] == c
					|| s[i + 1] == '\0')) || (s[i] == c && s[i + 1] == '\0'))
		{	
			wordcount++;
			i++;
		}		
		else
			i++;
	}
	return (wordcount);
}

int	len_field(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += find_end_quote(s + i, s[i]);
		else
			i++;
	}
	return (i);
}

char	**new_char_tab(char **str1, char **str2)
{
	char	**res;
	int		count;

	count = str_table_counter(str1) + str_table_counter(str2) + 1;
	count *= sizeof(char *);
	res = memset_alloc(0, count);
	if (!res)
		return (NULL);
	return (res);
}
