/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:37:22 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 12:07:47 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	unquoter_loop(t_tok_list *list)
{
	t_tok_link	*link;

	link = list->first;
	while (link != NULL)
	{
		unquote_link(link);
		link = link->next;
	}
	return (0);
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
	return (i);
}

char	*unquoter(char *str)
{
	int	i;
	int	mem;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			mem = find_end_quote(str + i, str[i]) + 1;
			squash(str, i);
			i += mem - 2;
			squash(str, i);
		}
		else
			i++;
	}
	return (str);
}

int	squash(char *str, int start)
{
	int	i;

	i = start + 1;
	while (str[i] != '\0')
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = '\0';
	return (0);
}
