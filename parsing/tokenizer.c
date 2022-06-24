/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/24 14:38:33 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"

typedef struct s_tok_link
{
	int					*meta;
	char				*str;
	struct s_tok_link	*next;
	struct s_tok_link	*prev;
}		t_tok_link;

typedef struct s_tok_list
{
	unsigned int		len;
	struct s_tok_link	*first;
	struct s_tok_link	*last;
}		t_tok_list;
/*
parse_token(char *str), un token par str ou metachar, separated stupidly
make_list
parse_str
expand
check_errors for metastr incoherences(during metaparse? after all tokens are created?)
*/
//  |  < et << peuvent etres colles a des str et continuer a fonctionner, > >> problement aussi

//mais si metachars are consequents in a wrong way, message "process : parse error near (symbol that's a problem)"
// zsh: parse error near `>'

t_tok_list	tokenizerstart(char *input)
{
	t_tok_list	*list;
	
	list = make_list();
	sep_token(input, list);
	expand_var(list);
	//print token list;
	return (list);
}

t_tok_list make_list()
{
	t_tok_list	*list;

	list = malloc(sizeof(t_tok_list));
	list->len = 0;
	list->first = NULL;
	list->last = NULL;
	return (list);
}

//strparser et metaparser cree le maillon, et malloc la bonne taille pour la str 
//strndup(str, len)
void	sep_token(char *str, t_tok_list *list)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		while (isspace(str[i]) == YES)
			i++;
		if (is_meta (str[i]) == NO)
		{
			//i += strparser(list, str + i) //manage start and end of quotes as a single block of str
			j = i;
			i++;
			while (ft_isinstr (str[i]) == 1)
				i++;
			token[z] = strndup(str + y, i - y - 1);
			z++;
		}
		if (is_meta (str[i]) == YES)
		{
			//i += metaparser(list, str + i)
			token[z] = metaparser(str, i);		
		}
	}
}

int	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	else
		return (NO);
}

int	strparser(t_tok_list *list, char *str)
{
	int	i;
	t_tok_link *link;

	i = 0;
	link = make_add_link(list);
	while (is_meta (str[i]) == NO && isspace(str[i]) == NO)
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i);
		else
			i++;
	}
	list->last->str = ft_strndup(str, i);
	list->last->meta = CMD;
	return (i);
}

int	metaparser(t_tok_list *list, char *str)
{
	int	i;
	t_tok_link *link;

	i = 0;
	link = make_add_link(list);
	i += metachar_parser(str)
	list->last->str = ft_strndup(str, i);
	//is strlen(str) == 1 or 2, problem!(possibly super simple way of finding input error??!)
	list->last->meta = 0;
	return (i);	
}

int	find_end_quote(char *str)
{
	int		i;
	char	quote;
	
	i = 1;
	quote = str[0];
	while (str[i] != quote && str[i] != '\0')
	{
		i++;
	}
	return (i);
}




/*
BUT : fournir une liste chaine cree a partir de inputstr
->parcourir str, creer un maillon pour chaque mot complet, metachar seul et str entre quotes
ignorer les espaces pas entre quotes,
return liste avec un maillon par str, a reassembler par lexer ensuite en cmdstr et metachar important
redirections et leurs cibles en un seul token? OUI, avec type defini
meme chose pour heredoc start et son EOF? OUI
*/

int	metachar_parser(char *str)
{
	if (strncmp(str, "<<", 2) == 0)
		return (xx(str + 2) + 2)
	if (strncmp(str, "<", 1) == 0)
		return (xx(str + 1) + 1)
	if (strncmp(str, ">>", 2) == 0)
		return (xx(str + 2) + 2)
	if (strncmp(str, ">", 1) == 0)
		return (xx(str + 1) + 1)
	if (strncmp(str, "|", 1) == 0)
		return (1);
}

int	duplicate_str_finder(char *str)//can be fused later with str parser
{
	int	i;

	i = 0;
	while (isspace(str[i]) == YES)
		i++;
	while (is_meta (str[i]) == NO && isspace(str[i]) == NO)
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i);
		else
			i++;		
	}
	return (i);	
}

/*
nested quotes:
if char[i] == '\'' ou '\"'

i++ until quotes, if same as start, end of quoted str,
else, new cycle with other quoteas start,
repeat until EOF or end of every quotes
if EOF, error
else, full str is between first quote and end of last cycle closed;

no need to remember except the last end quote, and start position is always to keep anyway
can be a recursive cycle of same function who only return last position and add to i
!!PB, $VAR must expand if only between "", could be slightly annoying to find if opened '' when $VAR
but functions for quotes could give beginning and end position too...
lots of parameter for a single string...could keep coordinates of '' "zones" for this string?
maybe in struct of link?

need to parse >> before >
and << before <
not separate automatically every metachar from char immediatly next? NEED TESTS!! 
*/

/*
could use a program test exec by minishell
cmd "binary arg1arg2 'arg3'arg4"
and it gives number et format of args it received?
*/
