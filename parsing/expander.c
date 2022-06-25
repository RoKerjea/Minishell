
/*Parcourir les str de gauche a droite, suivant les cas de $x(et quotes), translate from env ou delete/ignore
do i need to split the str to translate and then rejoin?, maybe...
seems to be translated from left to right litterally...
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
(print rien "")"*/

/*
is $$ an env variable? NON, donc pas a gerer, et a transformer en ""! (delete)
expansion happen BEFORE wildcards patternization and substitution
*/