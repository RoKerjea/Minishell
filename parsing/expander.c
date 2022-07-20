/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:06:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/20 20:39:17 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

//expander function, to be used after tokenizer but before parser
//send input str back but with $VAR replaced by its content in env
void	token_expander(t_tok_list *list, t_env *local_env)
{
	t_tok_link	*token;
	char		*expanded;

	token = list->first;
	while (token != NULL)
	{
		printf ("gateexpandtok\n");
		if (strchr(token->str, '$') != 0)
		{
			expanded = expander(token->str, local_env);
			//protect
			free (token->str);
		}
		token->str = expanded;
		token = token->next;
	}
}

char	*expander(char *str, t_env *local_env)
{
	printf ("gateexpander\n");
	unsigned int	i;
	unsigned int	last_var;
	int				quote;
	char			*res;
	char			*temp;
	
	quote = -1;
	i = 0;
	res = malloc(1);
	res[0] = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quote *= -1;//pas tres beau, mais ca signale si on est a l'interieur de "" ou non (-1 exterieur, 1 interieur)
		if (str[i] == '\'' && quote == -1)
			i += find_end_quote(str + i, '\'');//si les ' sont entre des "" actifs, ils ne comptent pas!
		else if (str[i] == '$')
		{
			
			res = expand_res(str, i, local_env);
			i += wordlen(str + i);
			last_var = i;
		}
		else
			i++;
	}
	printf ("gateexpandedres res = %s\n", res);
	temp = ft_strjoin(res, ft_strdup(str + last_var));
	free (res);
	res = temp;
	//make an strdup of whats AFTER last variable, and join(res, laststr);
	printf ("expanded str = %s\n", res);
	return (res);
}

int	expand_res(char *str, int i, t_env *local_env)
{
	printf ("gateexpandres\n");
	char	*str1;
	char	*str2;
	char	*res;

	str1 = ft_strndup(str, i - 1);
	str2 = get_var_content(str + i, local_env);
	printf ("gateexpandres2, str1 = %s, str2 = %s\n", str1, str2);
	res = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	printf ("gateexpandres res = %s\n", res);
	return (res);
}

char	*get_var_content(char *str, t_env *local_env)
{
	printf ("gategetvar\n");
	char	*res;
	char	*name;
	
	name = extract_name(str);
	printf ("gategetvar2, name = %s\n", name);
	//parsename for particular cases ($" and $') and their return
	//what if name start by $ or other metachar?(error)
	t_env_link		*link;
	link = find_link(name, local_env);
	if (link == NULL)
		return (NULL);
	printf ("gategetvar4, content of var = %s\n", link->variable);
	res = ft_strdup(link->variable);
	free (name);
	return (res);
}

char	*extract_name(char *str)
{
	printf ("gateextract\n");
	char	*name;
	int	i;
	
	i = wordlen(str);
	name = ft_strndup(str + 1, i);
	return (name);
}

int	wordlen(char *str)
{
	printf ("gatelen\n");
	int	i;
	
	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) == NO)
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