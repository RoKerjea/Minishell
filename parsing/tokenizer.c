/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/22 21:20:46 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct s_tok_link
{
	int					*meta;
	char				*str;
	struct s_tok_link	*next;
	struct s_tok_link	*prev;
}		t_tok_link;

typedef struct s_token_list
{
	unsigned int		len;
	struct s_tok_link	*first;
	struct s_tok_link	*last;
}		t_tok_list;

parse_token(char *str), un token par str ou metachar, separated stupidly
make_list
parse_str
expand
check_errors for metastr incoherences(during metaparse? after all tokens are created?)

//  |  < et << peuvent etres colles a des str et continuer a fonctionner, > >> problement aussi

//mais si metachars are consequents in a wrong way, message "process : parse error near (symbol that's a problem)"
// zsh: parse error near `>'

t_tok_list	tokenizerstart(char *input)
{
	t_tok_list	*list;
	list = make_list();
	sep_token(input, list);
	expand_var(list);
	return (list);
}

t_tok_list make_list()
{

}

//strparser et metaparser cree le maillon, et malloc la bonne taille pour la str 
//strndup(str, len)
void	sep_token(char *str, t_tok_list *list)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		while (isspace(str[i]) == 1)
			i++;
		if (is_meta (str[i]) == 0)
		{
			//i += strparser(list, str + i) //manage start and end of quotes as a single block of str
			j = i;
			i++;
			while (ft_isinstr (str[i]) == 1)
				i++;
			token[z] = strndup(str + y, i - y - 1);
			z++;
		}
		if (is_meta (str[i]) == 1)
		{
			//i += metaparser(list, str + i)
			token[z] = metaparser(str, i);		
		}
	}
}

/*Parcourir les str de gauche a droite, suivant les cas de $x(et quotes), translate from env ou delete/ignore
do i need to split the str to translate and then rejoin?, maybe...
*/
void	expand_var(list)//need to delete exterior quotes of str
{
	
}

/*
BUT : fournir une liste chaine cree a partir de inputstr
->parcourir str, creer un maillon pour chaque mot complet, metachar seul et str entre quotes
ignorer les espaces pas entre quotes,
return liste avec un maillon par str, a reassembler par lexer ensuite en cmdstr et metachar important
redirections et leurs cibles en un seul token? OUI, avec type defini
meme chose pour heredoc start et son EOF? OUI
*/

/*
quotes:
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

//need mini pasrser step after tokenizer?

/*
if $VAR$VAR$VAR, can i separate them in tokens?
if "ste $VAR str " can i tokenized to then expand and still remake the str original between ""?
can i just split in three, expand 2, and then rejoin?
could i tokenize a full string and only then expand it?
what if $VAR doesn't exist? $"$VAR", 
!! if $VAR doesn't exist, $ is deleted, and VAR is just an str of char, can just parse from left to right then?
*/

/*4 cas de "$x" a parser donc
x = EXIST -> content
x = WRONG -> "" (empty)
x = ' -> $ is deleted
x = " -> $ is a char forever in THIS minishell
*/

if $", $ is a char,
if $', $ is deleted,
if $WRONG, all of it mean ""



echo $"rfrgrg"
$rfrgrg

diff de :

echo $'rfrgrg'
rfrgrg

et diff de

echo $rfrgrg
(print rien "")"