/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:19 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/25 21:04:42 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"

typedef struct s_parsed_link
{
	int						*type;//defini en MACRO avec un int pour CMD, PIPE, IN, OUT, HEREDOC, APPEND, (BUILTIN?)
	char					*cmd;//to use to find path if needed, or for builtin select... 
								//une liste de str* avec str[0] pour la cmd, donc facile a parser pour builtins, path absolu ou relatif etc
	char					**args;//pour les arguments et options(args[0] SHOULD be the cmd name, by convention)
	int						*fdins;//list de fdin pour la cmd, avec seulement la derniere a utiliser(2, 3, 4 ou rien) but need to open and close all others...
	char					**fdins_args;//cible des redirections correspondantes a leurs fdins...
	int						*fdouts;// (2, 5, 6 ou rien)
	char					**fdouts_args;//cibles si il y a
	struct s_parsed_link	*next;//if NULL, first cmd, if not NULL, pipe fdin exist but maybe not used for this cmd
	struct s_parsed_link	*prev;//if NULL, last cmd, if both NULL, only one cmd, so no pipe, and no fork for builtins
}		t_parsed_link;

typedef struct s_parsed
{
	unsigned int			len;
	struct s_parsed_link	*first;
	struct s_parsed_link	*last;
}		t_parsed;

t_tok_link	*link;
t_tok_list	*list;

/*
BUT : Fournir une liste chainee avec des inputs fixes pour les commandes et un type en int defini en macro pour builtin or exec
list of tokens with type and *str separe, les espaces ignores si ils sont a l'exterieur de quotes,
les metachars dans leurs str* a part(si pas inside quotes)

HOW: Make a link by command, adding in and out as params, until find pipe | or end of list?
can be used to get args after redir all in one link
only need to get redirections in order from left to right and use the last one
maybe split spaces for args of cmd(optional for now)
temp struct to store various variable?
until | or NULL
if 3 or 4, in fdin redir
if 5 or 6 , in fdout redir
if 1, to cmd, one by one
once finished, find builtins for types
if a field cmd is empty, errors
if redir empty, either pipe or stdandartfd, depending if first/last link(prev ==NULL) or not
need to test redir of multiple args if args come from $VAR(var="arg1 arg2")
expander cycle on every str, then split for cmd args?
what if cmd is in $VAR? then expand first and then char *cmd and char **args(but what if VAR should be splitted in redir? ignore, multi redir?)
*/

typedef struct s_temp
{
	t_tok_link	*cmd_list_first;
	t_tok_link	*cmd_list_last;
	t_tok_link	*in_list_first;
	t_tok_link	*in_list_last;
	t_tok_link	*out_list_first;
	t_tok_link	*out_list_last;
	t_temp		*next;

}	t_temp;


t_temp	*token_sorter(t_tok_list	*list)
{
	t_tok_link	*link;
	t_temp		*temp;
	
	temp = mktemplist();
	link = list->first;
	while (link != NULL)
	{
		if (link->meta == CMD)
			add_cmd(temp, link);
		if (link->meta == IN || link->meta == HEREDOC)
			add_in(temp, link);
		if (link->meta == OUT || link->meta == APPEND)
			add_out(temp, link);
		if (link->meta == PIPE)
		{
			update_next_tokens(temp);
			temp->next = mktemplist();
			temp = temp->next;
		}
		link = link->next;
	}
	return (temp);
}

/*
make a char **str for cmds and args, or just char* for cmd AND char** for args?

/*
ls <in -l <in2 -a
est valide en tant que "ls -l -a" avec deux redir in!!

expander step AFTER parser end(but last re-check needed?)
*/