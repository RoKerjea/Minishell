/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:13:48 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/20 20:57:23 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"
#include "../include/macro.h"

// create the list, no links in yet
t_tok_list	*make_list(void)
{
	t_tok_list	*list;

	list = memset_alloc(0, sizeof(t_tok_list));
	if (list == NULL)
		return (NULL);
	return (list);
}

// create a new empty link and add it at the last place in the list
t_tok_link	*make_add_link(t_tok_list *list)
{
	t_tok_link	*link;

	link = memset_alloc(0, sizeof(t_tok_link));
	if (link == NULL)
		return (NULL);
	if (list->len == 0)
		list->first = link;
	else
	{
		list->last->next = link;
		link->prev = list->last;
	}
	list->last = link;
	list->len++;
	return (link);
}

void	destroy_token(t_tok_link *link)
{
	if (link->str)
		ft_freetab(link->str);
	free(link);
}

void	destroy_token_list(t_tok_list *list)
{
	t_tok_link	*link;
	t_tok_link	*nextlink;

	link = list->first;
	while (link != NULL)
	{
		nextlink = link->next;
		destroy_token(link);
		link = nextlink;
	}
	free (list);
}
