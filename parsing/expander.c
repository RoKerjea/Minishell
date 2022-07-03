/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:06:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/03 19:15:21 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"

//expander function, to be used after tokenizer but before parser, exec and builtins receive expanded str
char	*expander(char *str, t_env *local_env)
{
	unsigned int	i;
	unsigned int	last_var;
	unsigned int	quote;
	char			*res;
	char			*temp;
	
	quote = -1;
	i = 0;
	res = "";
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quote *= -1;//pas tres beau, mais ca signale si on est a l'interieur de "" ou non (-1 exterieur, 1 interieur)
		if (str[i] == '\'' && quote == -1)
			i += find_end_quote(str + i, '\'');//FUCK, si les ' sont entre des "" actifs, ils ne comptent pas!
		else if (str[i] == '$')
		{
			i += expand_res(str, i, local_env, res);
			last_var = i;
		}
		else
			i++;
	}
	temp = ft_strjoin(res, ft_strdup(str + last_var));
	free (res);
	res = temp;
	//make an strdup of whats AFTER last variable, and join(res, laststr);
	return (res);
}

int	expand_res(char *str, int i, t_env *local_env, char *res)
{
	char	*str1;
	char	*str2;

	str1 = ft_strndup(str, i - 1);
	str2 = get_var_content(str + i, local_env);
	if (ft_strlen(res) > 0)
		free (res);
	res = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	return (wordlen(str + i));
}

char *get_var_content(char *str, t_env *local_env)
{
	char	*res;
	char	*name;
	
	name = extract_name(str);
	//parsename for particular cases ($" and $') and their return
	res = ft_strdup(get_env_var(name, local_env));
	free (name);
	return (res);
}

char	*extract_name(char *str)
{
	char	*name;
	int	i;
	
	i = wordlen(str);
	name = ft_strndup(str, i);
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
//$VAR FILE.c -> make an expander ft to be called from everywhere?
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
"$foo" make a SINGLE str, even with spaces inside
while
$foo make AS MANY str as spaces separator +1 (foo="arg1 arg2" give two separate str)

! TO TEST: "$ "; "$"

is $$ an env variable? NON, donc pas a gerer, et a transformer en ""! (delete)
expansion happen BEFORE wildcards patternization and substitution
*/