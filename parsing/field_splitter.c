/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:35:17 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 12:49:38 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/macro.h"
#include "../include/utils.h"

char	**make_new_str(char *s, char c, int wnum, char **res)
{
	int	i;
	int	lenfield;

	i = 0;
	while (wnum < field_counter(s, c))
	{
		while (s[i] == c)
			i++;
		lenfield = len_field(s + i, c);
		res[wnum] = ft_strndup(s + i, lenfield);
		if (!(res[wnum]))
			return (ft_freetab(res));
		i += lenfield;
		wnum++;
	}
	return (res);
}

char	**field_splitter(char *s, char c)
{
	char	**res;
	int		wnum;

	wnum = field_counter(s, c);
	res = (char **)malloc(sizeof(char *) * (wnum + 1));
	if (!res)
		return (NULL);
	res[wnum] = NULL;
	if (wnum == 1)
	{
		res[0] = ft_strtrim(s, " ");
		return (res);
	}
	wnum = 0;
	res = make_new_str (s, c, wnum, res);
	return (res);
}

int	token_splitter(t_tok_list	*list)
{
	t_tok_link	*token;
	char		**splitted;

	token = list->first;
	while (token != NULL)
	{
		if (ft_strchr(token->str[0], ' ') != 0)
		{
			splitted = field_splitter(token->str[0], ' ');
			if (token->meta == IN || token->meta == OUT
				|| token->meta == APPEND)
			{
				if (splitted[1] != NULL)
				{
					ft_putstr_fd("minishell : ambiguous redirect\n", 2);
					ft_freetab(splitted);
					return (NO);
				}
			}
			ft_freetab(token->str);
			token->str = splitted;
		}
		token = token->next;
	}
	return (YES);
}

int	first_tab(char	**res, char **str1)
{
	int	i;

	i = 0;
	while (str1[i] != NULL)
	{
		res[i] = ft_strdup(str1[i]);
		if (!res[i])
		{
			ft_freetab(str1);
			ft_freetab(res);
			return (-1);
		}
		i++;
	}
	ft_freetab(str1);
	return (i);
}

char	**char_tab_fuser(char **str1, char **str2)
{
	char	**res;
	int		i;
	int		j;

	res = new_char_tab(str1, str2);
	if (!res)
		return (NULL);
	i = first_tab(res, str1);
	if (i == -1)
		return (NULL);
	j = 0;
	while (str2[j] != NULL)
	{
		res[i] = ft_strdup(str2[j]);
		if (!res[i])
			return (ft_freetab(res));
		i++;
		j++;
	}
	res[i] = NULL;
	return (res);
}
