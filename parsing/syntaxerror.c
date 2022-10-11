/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:13:23 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 14:19:26 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/macro.h"
#include "../include/utils.h"
#include "../include/parsing.h"

int	syntaxerror_print(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (NO);
}

int	syntax_error(t_tok_link *link)
{
	if (link->meta == IN || link->meta == OUT
		|| link->meta == HEREDOC || link->meta == APPEND)
	{
		if (link->str[0][0] == '\0')
			return (syntaxerror_print(link->next->str[0]));
	}
	if (link->meta == PIPE)
	{
		if (link->next->meta == PIPE || link->next->meta == END)
			return (syntaxerror_print(link->next->str[0]));
		if (link->prev == NULL)
			return (syntaxerror_print(link->str[0]));
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
