/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:37:22 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/21 20:21:21 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int find_end_quote(char *str, char c)
{
	int i;

	printf("gate quote %s\n", str); // TEST to delete
	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	//what if str[i] == '\0'?? then big error for all inputstr!
	return (i + 1);
}

int	unquoter_loop(t_tok_list *list)
{
	t_tok_link *link;

	link = list->first;
	while (link != NULL)
	{
		unquote_link(link);
		link = link->next;
	}
	return 0;
}

int	unquote_link(t_tok_link *link)
{
	int	i;

	i = 0;
	while (link->str[i] != NULL)
	{
		unquoter(link->str[i]);
		i++;
	}
}

char	*unquoter(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += find_end_quote(str, str[i]);
		}
		i++;
	}
	return (str);
}

int	main(void)
{
	char	*str;
	str = malloc (sizeof(char) * 19);
	str = "ceci est un test!\n";
	str + 4 = str + 5;
	return(0);
}
//ergerg'retwer'w