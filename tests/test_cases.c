/*
ls <in -l <in2 -a
est valide en tant que "ls -l -a" avec deux redir in!!

4 cas de "$x" a parser:
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
(it's just the space as str sep in normal cases and quotes are single str rules!)
! TO TEST: "$ "; "$"

is $$ an env variable? NON, donc pas a gerer, et a transformer en ""! (delete)

//  |  < et << peuvent etres colles a des str et continuer a fonctionner, > >> problement aussi

// mais si metachars are sequentials in a wrong way, message "process : parse error near (symbol that's a problem)"
//  zsh: parse error near `>'

could use a program test exec by minishell
cmd "binary arg1arg2 'arg3'arg4"
and it gives number et format of args it received?

need to parse >> before >
and << before <


strace -ff -e open,close,unlink,read,write,execve,dup2,clone sh heredoc_bash.sh


are there fd that stay opens even after they stop being useful

*/