/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 17:52:07 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"
#include "../include/macro.h"

// FILE: what's needed to make list of tokens from input, depending of their type
// INPUT: the full line from readline (xx)
// OUTPUT: liste chainee de token contenant seulement les '|', str pour cmd,
// et redirections avec leurs cibles

/*
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
*/

/*
parse_token(char *str), un token par str ou metachar, separated stupidly
check_errors for metastr incoherences(during metaparse? after all tokens are created?)
*/

//  |  < et << peuvent etres colles a des str et continuer a fonctionner, > >> problement aussi

// mais si metachars are sequentials in a wrong way, message "process : parse error near (symbol that's a problem)"
//  zsh: parse error near `>'

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

// start of tokenizer, create list of token, launch token separator,
// check result of this step (if redirection have their arguments)
t_tok_list *tokenizerstart(char *input)
{
	t_tok_list *token_list;

	token_list = make_list();
	printf("len of input == %lu\n", strlen(input)); // TEST to delete
	sep_token(input, token_list);
	if (syntax_checker(token_list) == NO)
		printf("problem and should free list and stop current input\n"); // TEST to delete, but replace with a prob manager
	return (token_list);
}

// create the list, no links in yet
t_tok_list *make_list()
{
	t_tok_list *list;

	list = malloc(sizeof(t_tok_list));
	list->len = 0;
	list->first = NULL;
	list->last = NULL;
	return (list);
}

// create a new empty link and add it at the last place in the list
t_tok_link *make_add_link(t_tok_list *list)
{
	t_tok_link *link;

	link = malloc(sizeof(t_tok_link));
	if (list->len == 0)
	{
		list->first = link;
		link->prev = NULL;
	}
	else
	{
		list->last->next = link;
		link->prev = list->last;
	}
	link->next = NULL;
	list->last = link;
	list->len++;
	return (link);
}

// strparser et metaparser cree le maillon, et malloc la bonne taille pour la str
// strndup(str, len)
void sep_token(char *str, t_tok_list *list)
{
	int i;

	i = 0;
	printf("strart of tokenzer\n");	   // TEST to delete
	printf("//input== \"%s\"\n", str); // TEST to delete
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]) == YES && str[i] != '\0')
			i++;
		if (is_meta(str[i]) == NO && str[i] != '\0')
		{
			printf("start of strsep for char %d\n", i); // TEST to delete
			i += strparser(list, str + i);				// manage start and end of quotes as a single block of str
			printf("end of strsep for char %d\n", i);	// TEST to delete
		}
		else if (is_meta(str[i]) == YES && str[i] != '\0')
		{
			printf("start of metasep for char %d\n", i); // TEST to delete
			i += metaparser(list, str + i);
			printf("end of metasep for char %d\n", i); // TEST to delete
		}
	}
}

// get str until EOL or metachar, presumably part of same cmd for exec
int strparser(t_tok_list *list, char *str)
{
	int i;
	t_tok_link *link;

	i = 0;
	link = make_add_link(list);
	while (is_meta(str[i]) == NO && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i, str[i]);
		else
			i++;
	}
	printf("str in strparse == \"%s\", strlen = %d\n", str, i); // TEST to delete
	link->str = ft_strndup(str, i);
	printf("str made == \"%s\"\n", link->str); // TEST to delete
	link->meta = CMD;
	return (i);
}

// get str starting from metachar->create a token with metachar and redirection target, if any,
int metaparser(t_tok_list *list, char *str)
{
	int i;
	t_tok_link *link;

	i = 0;
	link = make_add_link(list);
	i += metachar_parser(str);
	printf("str in metaparse == \"%s\", strlen = %d\n", str, i); // TEST to delete
	link->str = ft_strndup(str, i);
	link->meta = meta_type(link->str);
	return (i);
}

// identify the type of redirection the current token is
int meta_type(char *str)
{
	if (strncmp(str, "<<", 2) == 0)
		return (HEREDOC);
	if (strncmp(str, "<", 1) == 0)
		return (IN);
	if (strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (strncmp(str, ">", 1) == 0)
		return (OUT);
	if (strncmp(str, "|", 1) == 0)
		return (PIPE);
	else
		return (0);
}

// find & return the length of the str between quotes c
int find_end_quote(char *str, char c)
{
	int i;

	printf("gate quote %s\n", str); // TEST to delete
	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i + 1);
}

// fnd & return the length of meta token, from the metachar,
// to the end of it's arg, if any
int metachar_parser(char *str)
{
	if (strncmp(str, "<<", 2) == 0 || strncmp(str, ">>", 2) == 0)
		return (meta_and_arg_size(str + 2) + 2);
	if (strncmp(str, "<", 1) == 0 || strncmp(str, ">", 1) == 0)
		return (meta_and_arg_size(str + 1) + 1);
	if (strncmp(str, "|", 1) == 0)
		return (1);
	else
		return (0);
}

// find & return the length of arg of redirection token
int meta_and_arg_size(char *str) // could be fused later with str parser?
{
	int i;

	i = 0;
	while (ft_isspace(str[i]) == YES && str[i] != '\0')
		i++;
	while (is_meta(str[i]) == NO && ft_isspace(str[i]) == NO && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i, str[i]);
		else
			i++;
	}
	return (i);
}

/*
BUT : fournir une liste chaine cree a partir de inputstr
->parcourir str, creer un maillon pour chaque mot complet, metachar avec leurs arguments et str entre quotes
ignorer les espaces pas entre quotes,
return liste avec un maillon par str, a reassembler par parser ensuite en cmdstr et metachar important
redirections et leurs cibles en un seul token? OUI, avec type defini meme
meme chose pour heredoc start et son EOF? OUI
*/

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
