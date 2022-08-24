/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:06:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/24 18:42:33 by rokerjea         ###   ########.fr       */
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
		if (strchr(token->str[0], '$') != 0)
		{
			expanded = prototype(token->str[0], local_env);
			//protect
			free (token->str);
			token->str[0] = expanded;
		}
		token = token->next;
	}
}

/*si split(str, '$')
then, expand first word after *str[0]
replace,
rejoin all??
*/
char	*prototype(char *str, t_env *local_env)
{
	char	*res;
	int		i;
	int		j;
	t_word	*wordlink;
	t_word	*firstword;
	int		quote;

	quote = -1;
	i = 0;
	j = 0;
	wordlink = make_word_link("", 1);
	firstword = wordlink;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quote *= -1;//pas tres beau, mais ca signale si on est a l'interieur de "" ou non (-1 exterieur, 1 interieur)
		if (str[i] == '\'' && quote == -1)
			i += find_end_quote(str + i, '\'');//si les ' sont entre des "" actifs, ils ne comptent pas!
		else if (str[i] == '$')
		{
			if (i > j && j > 0)
				wordlink = make_add_wordlink(str + (j - 1), i - j + 1, wordlink);
			else if (i > j)
				wordlink = make_add_wordlink(str + j, i - j, wordlink);
			wordlink = make_add_wordlink(str + i, wordlen(str + i), wordlink);
			i += wordlen(str + i) + 1;
			j = i;
		}
		else
			i++;
	}
	if (j != i)
		wordlink = make_add_wordlink(str + (j - 1), i - j + 1, wordlink);
	res = fuse_and_clean(firstword, local_env);
	return (res);
}

void	wordlink_destroyer(struct s_word *firstword)
{
	struct	s_word	*tempword;
	struct	s_word	*wordlink;
	
	wordlink = firstword->next;
 	while (wordlink != NULL)//loop of destroy, starting from first;
	{
		tempword = wordlink->next;
		free (wordlink->word);
		free (wordlink);
		wordlink = tempword;
	}	
	return ;
}

char	*fuse_and_clean(struct	s_word *wordlink, t_env *local_env)
{
	struct s_word	*firstword;
	char			*temp;
	char			*res;

	res = malloc(1);
	res[0] = '\0';
	firstword = wordlink;
	while (wordlink != NULL)
	{
		//printf ("word in curr link = %s \n", wordlink->word);
		wordlink = wordlink->next;
	}
	wordlink = firstword->next;
	while (wordlink != NULL)//loop of expander
	{
		if (wordlink->word[0] == '$')
		{
			temp = get_var_content(wordlink->word, local_env);
			free (wordlink->word);
			wordlink->word = temp;
			if (wordlink->word == NULL)
			{
				wordlink->word = malloc(1);
				wordlink->word[0] = '\0';
			}
		}
		wordlink = wordlink->next;
	}
	//printf ("gatefuseclean02 \n");
	wordlink = firstword;
	while (wordlink != NULL)
	{
		//printf ("word in curr link after exp = %s \n", wordlink->word);
		wordlink = wordlink->next;
	}
	wordlink = firstword->next;
	while (wordlink != NULL)//res = loop of fuse, starting from second;
	{
		temp = ft_strjoin(res, wordlink->word);
		free (res);
		res = temp;
		wordlink = wordlink->next;
	}
	wordlink_destroyer(firstword);
/* 	wordlink = firstword->next;
	struct	s_word	*tempword;
 	while (wordlink != NULL)//loop of destroy, starting from first;
	{
		tempword = wordlink;
		free (wordlink->word);
		free (wordlink);
		wordlink = tempword->next;
	} */
	return (res);
}


struct	s_word	*make_word_link(char *str, int len)
{
	struct	s_word	*wordlink;

	wordlink = malloc(sizeof(struct	s_word));
	wordlink->word = strndup(str, len);
	wordlink->next = NULL;
	return (wordlink);
}

struct	s_word	*make_add_wordlink(char *str, int len, struct	s_word *prevword)
{
	struct s_word	*now_word;

	now_word = make_word_link(str, len);
	prevword->next = now_word;
	return (now_word);
}

char	*get_var_content(char *str, t_env *local_env)
{
	/*
	need
	if (name == $?)
	return(itoa(local_env->lst_exit));
	*/
	char		*res;
	char		*name;
	t_env_link	*link;

	name = extract_name(str);
	printf ("gategetvar2, name = %s\n", name);
	//parsename for particular cases ($" and $') and their return
	//what if name start by $ or other metachar?(error)	
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
	char	*name;
	int		i;

	i = wordlen(str);
	name = ft_strndup(str + 1, i - 1);
	return (name);
}

int	wordlen(char *str)
{
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