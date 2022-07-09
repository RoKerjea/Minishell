/*
"cmd *" will exec cmd to every valid file and dir found with *
*str, str*, *str* and any combination *str*str*str[...]
get every names of files and/or directories and keep them in charres** (in x order)
start comparaison in first char*, if true, keep in new charres** or keep index in int*
if false, check next char*
end of charin**, send new charres**(created after knowing wich of charin** are true)

how to find if pattern==true?
if char[0] == char and not *, test comp char[0]
if char[0] == * can be anything
already too complex for later...
search fixed str != * in pattern, add to char pattern**?
if '*' in pattern add '*' to char pattern**
once pattern is gone through, we have a char pattern**
with strings of "*" and char* in order;
then
we can go through to charin[x], one by one
if pattern[x] == "*"
char[x++] until we find the entirety of pattern[x+1]
repeat;
if end of charin[x], and not end of pattern, 
name is wrong for pattern,
if end of pattern (or, last str of char =! '*')
then name true for pattern, charin[x][y], x is an int to keep in memory for final charres**
(ou, linked list of results, addback char[x] to result, way easier for variable length of results)
*/