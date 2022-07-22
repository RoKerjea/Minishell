/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:35:17 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/22 13:20:53 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
/* 
// find & return the length of the str between quotes c
int find_end_quote(char *str, char c)
{
	int i;

	printf("gate quote %s\n", str); // TEST to delete
	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	printf("char inquote= %d\n", i);
	//what if str[i] == '\0'?? then big error for all inputstr!
	return (i);
}

char	*ft_strndup(const char *s1, int j)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * (j + 1));
	while (i < j && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		if (tab[i])
			free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
} */

int	field_counter(char *s, char c)
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
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			wordcount++;
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
		{
			i += find_end_quote(s, s[i]);
		}
		i++;
	}
	return (i + 1);
}

char	**field_splitter(char *s, char c)
{
	printf("input = %s\n", s);
	char	**res;
	int		wnum;
	int		lenfield;

	wnum = field_counter(s, c);
	res = (char **)malloc(sizeof(char *) * (wnum + 1));
	if (!res)
		return (NULL);
	printf("num of field = %d\n", wnum);
	res[wnum] = 0;
	wnum = 0;
	while (res[wnum] != 0)
	{
		while (s[0] == c)
			s++;
		lenfield = len_field(s, c);
		res[wnum] = ft_strndup(s, lenfield);
	 	if (!(res[wnum]))
			return (ft_freetab(res));
		s += lenfield;
		wnum++;
	}
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
			printf("inputpresplit = %s\n", token->str[0]);
			splitted = field_splitter(token->str[0], ' ');
			ft_freetab(token->str);
			token->str = splitted;
			printf("inputpost split = %s\n", token->str[0]);
		}
		token = token->next;
	}
	return (0); 
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