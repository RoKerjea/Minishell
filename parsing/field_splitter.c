/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:35:17 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/08 23:02:12 by rokerjea         ###   ########.fr       */
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
		res[0] = ft_strdup(s);
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

/* int	main(int ac, char **av)
{
	char	**res;
	int i;
	i = 0;

	res = field_splitter("\'truc chouette\' chose", ' ');
	while (res[i] != NULL)
	{
		printf("str%d splitted = %s\n", i, res[i]);
		i++;
	}
	ft_freetab(res);
	return (0);
} */