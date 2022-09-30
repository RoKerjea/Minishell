/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:06:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/29 13:36:48 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

// CONTENT OF FILE: what's needed to expand content of tokenlink->str[0], correspondning to env variable
// INPUT: linked list of token
// OUTPUT: same list but with expander step executed on str

//expander function, to be used after tokenizer but before parser
//send input str back but with $VAR replaced by its content in env
void	token_expander(t_tok_list *list, t_env *local_env)
{
	t_tok_link	*token;
	char		*expanded;

	token = list->first;
	while (token != NULL)
	{
		if (ft_strchr(token->str[0], '$') != 0 && token->meta != HEREDOC
			&& token->meta != HEREDOC_NOEXPAND)
		{
			expanded = str_expander(token->str[0], local_env, 1);
			//protect
			//free (token->str[0]);
			token->str[0] = expanded;
		}
		token = token->next;
	}
}

char	*str_expander(char *str, t_env *local_env, int expand)
{
	int		quote;
	int		i;

	i = 0;
	quote = -1;
	while (str[i])
	{
		if (str[i] == '\"')
			quote *= -1;//pas tres beau, mais ca signale si on est a l'interieur de "" ou non (-1 exterieur, 1 interieur)
		if (str[i] == '\'' && quote == -1 && expand == 1)
			i += find_end_quote(str + i, '\'');//si les ' sont entre des "" actifs, ils ne comptent pas!
		else if (str[i] == '$')
		{
			if (quote == 1 && (str[i + 1] == ' ' || str[i + 1] == '\"'))
				i++;
			else if (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '+' || str[i + 1] == '=')
				i++;
			else
			{
				str = smartass(str, i, local_env);
				i = 0;
			}
		}
		else
			i++;
	}
	return (str);
}

char	*smartass(char *str, int i, t_env *local_env)
{
	char	*var;
	char	*left_str;
	char	*right_str;
	char	*temp;

	left_str = ft_strndup(str, i);
	right_str = get_right_str (str + i);
	var = get_var_content (str + i, local_env);
	temp = ft_strjoin (left_str, var);
	free (left_str);
	free (var);
	left_str = temp;
	temp = ft_strjoin(left_str, right_str);
	free (left_str);
	free (right_str);
	return (temp);
}

char	*get_right_str(char	*str)
{
	str += wordlen(str);
	return (ft_strdup(str));	
}

char	*get_var_content(char *str, t_env *local_env)
{
	char		*res;
	char		*name;
	t_env_link	*link;

	name = extract_name(str);
	if (!strncmp(name, "?", 3))
	{
		free (name);
		return(ft_itoa(local_env->lst_exit));
	}
	link = find_link(name, local_env);
	free (name);
	if (link == NULL)
		return (ft_strdup(""));
	res = ft_strdup(link->variable);
	return (res);
}

char	*extract_name(char *str)
{
	char	*name;
	int		i;

	i = wordlen(str);
	name = ft_strndup(str + 1, i - 1);
	return (name);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (YES);
	return (NO);
}

int	wordlen(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[i]))
		return (i + 1);
	while (str[i] != 36 && str[i] != '\0' && ft_isspace(str[i]) == NO && str[i] != '\"' && str[i] != '\'' && str[i] != '/' && str[i] != '=' && str[i - 1] != '?')
		i++;
	return (i);
}
/*
from left to right, until $, stdup(str, i), when $, find variable, stdup var, join str1 and str2,
same from end of $var in original string, repeat, until '\0'...
*/

/*Parcourir les str de gauche a droite, suivant les cas de $x(et quotes), translate from env ou delete/ignore
can go through str while str[i] != '\0'
and just i+= endquote if str[i] == '\'' and not already inside '\"'?
so, just one expand cycle before removing exterior quotes?
*/
//$VAR FILE.c -> make an expander ft to be called from everywhere? no, just before parser, once
//need mini parser step after tokenizer? why?? in case of errors? syntax error?
//syntax check happen BEFORE var expansion!
/*
if $VAR$VAR$VAR, can i separate them in tokens?
if "ste $VAR str " can i tokenized to then expand and still remake the str original between ""?
can i just split in three, expand 2, and then rejoin?
could i tokenize a full string and only then expand it?
what if $VAR doesn't exist? $"$VAR", 
!! if $VAR doesn't exist, $VAR is deleted, can just parse from left to right then?
*/
/*3 cas de "$x" a parser:
x = EXIST -> content
x = WRONG -> "" (empty)
x = ' || x == " -> $ is deleted (and then, quotes will be deleted)

echo $"rfrgrg"
rfrgrg

same as :

echo $'rfrgrg'
rfrgrg

but diff from

echo $rfrgrg
(print rien "")"

is managed in field splitting + quote remover
	"$foo" make a SINGLE str, even with spaces inside
	while
	$foo make AS MANY str as spaces separator +1 (foo="arg1 arg2" give two separate str)
	(it's just the space as str sep in normal cases and quotes are single str rules!)

! TO TEST: "$ "; "$"

is $$ an env variable? NON, donc pas a gerer, et a transformer en ""! (delete)
expansion happen BEFORE wildcards patternization and substitution(for '*' bonus)
*/