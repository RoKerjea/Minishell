/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:21:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/16 14:45:16 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/macro.h"
#include "../include/parsing.h"

// check if char input is a metachar, to be treated differently
int is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	else
		return (NO);
}

// check if char input is a space, to be treated differently
// space, tab, newline and possibly carriage return.
int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (YES);
	else
		return (NO);
}

// verif step for token, if a redirection doesn't have a target, problem
// syntax check happen BEFORE var expansion! so, last step of tokenizer
int syntax_checker(t_tok_list *list)
{
	t_tok_link *link;

	link = list->first;
	while (link != NULL)
	{
		if ((link->meta == IN || link->meta == OUT) && ft_strlen(link->str) < 2)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", link->next->str[0]); //! oups, what if link-nextn'existe pas?
			return (NO);
		}
		if ((link->meta == HEREDOC || link->meta == APPEND) && ft_strlen(link->str) < 3)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", link->next->str[0]);
			return (NO);
		}
		link = link->next;
	}
	return (YES);
}

