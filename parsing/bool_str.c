/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:21:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:17:38 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/macro.h"
#include "../include/utils.h"
#include "../include/parsing.h"

// check if char input is a metachar, to be treated differently
int	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	else
		return (NO);
}

// check if char input is a space, to be treated differently
// space, tab, newline and possibly carriage return.
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (YES);
	else
		return (NO);
}

int	syntax_error(t_tok_link *link)
{
	if (link->meta == IN || link->meta == OUT
		|| link->meta == HEREDOC || link->meta == APPEND)
	{
		if (link->str[0][0] == '\0')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(link->next->str[0], 2);
			ft_putstr_fd("'\n", 2);
			return (NO);
		}
	}
	if (link->meta == PIPE)
	{
		if (link->next->meta == PIPE || link->next->meta == END)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(link->next->str[0], 2);
			ft_putstr_fd("'\n", 2);
			return (NO);
		}
	}
	return (YES);
}

// verif step for token, if a redirection doesn't have a target, problem
// syntax check happen BEFORE var expansion! so, last step of tokenizer
//need write on fd 2!!
int	syntax_checker(t_tok_list *list)
{
	t_tok_link	*link;

	link = list->first;
	while (link != NULL)
	{
		if (!syntax_error(link))
			return (NO);
		link = link->next;
	}
	return (YES);
}

// find & return the length of the str between quotes c
int	find_end_quote(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i + 1);
}
