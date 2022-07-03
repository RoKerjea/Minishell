/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:06:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/03 16:08:57 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*Parcourir les str de gauche a droite, suivant les cas de $x(et quotes), translate from env ou delete/ignore
do i need to split the str to translate and then rejoin?, maybe...
seems to be translated from left to right litterally...
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
*/



/*
is $$ an env variable? NON, donc pas a gerer, et a transformer en ""! (delete)
expansion happen BEFORE wildcards patternization and substitution
*/