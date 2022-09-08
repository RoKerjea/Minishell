/*
Afficher un prompt en l’attente d’une nouvelle commande.
(probablement readline? puis wait until newline?)

Posséder un historique fonctionnel.
(haut bas, liste chainee de lignes de commandes finies?)

!!Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non
demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule).
(probablement juste print erreur explicite?)

Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets.
Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets sauf le $ (signe dollar).
(parcourir str jusqu'a trouver debut et fin des quotes? what about nested quotes?
then have active/inactive state for ignoring/interpreting metachar?)

Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
(variable must exist before being called)
probably "char *getenv(const char *name)" puis la var correspondante

Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline
exécutée au premier plan.
(exit(XX) of last process? pas sur de comprendre "pipeline",
"premier plan" veut probablement dire par rapport au process parent minishell, 
donc un int a garder en memoire ds struct globale)

if "<<"
<< doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
lire delimiteur valide (restrictions possibles?) puis lire ligne par ligne en
cherchant str END ds la string recue.
(c'est juste heredoc)

"<" doit rediriger l’entrée.
">" doit rediriger la sortie.
comme les STDIN OUT de pipex, je suppose, mais possiblement en interne aussi,
pas que au tt debut et a la tte fin!
">>" doit rediriger la sortie en mode append
* comme pour > mais en ecrivant a partir de la fin de ce fichier je suppose?

SIGNAUX
signals a gerer
Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
En mode interactif :
◦ ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
◦ ctrl-D quitte le shell.
◦ ctrl-\ ne fait rien.
get signals during heredoc(ctrl c, ctrl z) too
	sighandler_t signal(int signum, sighandler_t handler)  
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	int sigemptyset(sigset_t *set);
	int sigaddset(sigset_t *set, int signum);


BUILTINS
◦ echo et l’option -n
(-n fait juste ignorer le dernier \n)
ecrire ds le terminal avec l'input "deplie" pour les variable $xx
-nnnnnnn  et "-n -n -n -n -n" sont valides

◦ cd uniquement avec un chemin relatif ou absolu
	(int chdir(const char *path))
(modifier var PWD in ENV)
◦ pwd sans aucune option
	(char *getcwd(char *buf, size_t size))

◦ export sans aucune option
The  shell  shall give the export attribute to the
       variables corresponding to  the  specified  names,
       which shall cause them to be in the environment of
       subsequently executed commands. If the name  of  a
       variable  is  followed by =word, then the value of
       that variable shall be set to word.
	(update env with the specific variable i guess)

◦ unset sans aucune option
	reverse of export, get a variable out of env list
◦ env sans aucune option ni argument
	(it's just a print char** after getting update env, i guess)
◦ exit sans aucune option
	exit(0)?

every redirection dup is done in child process
but verification that they exist happen before

//TODO
separer la structr env du .h principal, vu qu'il est utile dans tt les modules, on peut l'include ds tt les differents .h
si la partie main n'a acces qu'au fonctions principales des modules(interacteur/porte d'entree)
le .h du main peut etre tres limite, pareil pour tout les modules et sous modules(builtins dans exec)
export qui trie en ordre ascii avec prefix

refacto, from the start...
malloc protection
leaks....(everywhere......)
struct destructors
message erreurs
cd - et cd~ maybe
$?
status sortie(avec signaux, probaby at the end, with $? + sigvalue)

char **env to create from t_env, and destructor(ft_freetab(xx))

heredoc!!(create temp folder, temp file, random names with target name as base for name)

pointeurs sur fonctions pour builtins(at the end, as bonus/practice)

parse error sur les multipipes("|||") ou ("| |")

not expand heredoc delimiter/name(check type o token before expander)
expand all content of heredoc if allowed(even if '$NAME' format inside a heredoc, single quotes INSIDE heredoc doesn't counts)
archi a revoir? fonctions externes seuls points de contacts entre modules et "master" functions

new .h limites avec des scopes precis pour pas mettre tout au meme endroit
env structs in other .h
*tokenizer
*expander
*splitter
*unquoter
*token assembler
*(redir parser)
*parsed list maker

//PRIORITIES
builtins don't need anything, and can be unified in style
	parse option -n and every combination(-nnnnnnn ------nn -n -n -n -n -n -n) for echo
how about char** for token, field splitting?, splitting happen AFTER expand,
	pre word count to malloc char**precisely at first, or
	splitting in temp var to then count easily and just put in right place after?
	if expander need to be split anyway, why not split everything at the same time?
	so need a way to split inside char* and return char**, and then fuse all char** in one char**
	what if char **str pour token, but only str[0] is used at first?
	then, split(str[0], ' ') ->temp, free previous char ** and replace with temp???
quote removal(trim start and end of char* i ?)
redirections(after expansion, field split, unquotes)
expander need to know how heredoc work
(line by line,
temp = expander(line, env)
write(fd, temp, ft_strlen(temp)))
free(line, tmp)
->nextline)
update
expand first str change cmd that will be executed(bash> $VAR, exec what's VAR after expansion)
$? is special expander and get return of exec and builtins(pretty much done)
redirections need heredocs to complete

signals need exec first
error messages, last to complete because need every possibilities, but can be added one by one
BUG
if cmd>str $PAGER str $USER str (fixed)
sometimes, !added at the end??
if env -i minishell, $PATH existe tout de meme!
exit arg (arg cannot be bigger than long long unsigned, before % 256, need strlen comp and atoll(arg) )

step by step:
merge basique
env fuser in char**
faire marcher sans builtins
faire marcher builtins
mettre les fonctions tests ds test.h
create script.sh for tests cases
diff with same 
gerer cas d'echecs particuliers

//BONUSES
1 - Les wildcards * doivent fonctionner pour le répertoire courant.
(donc QUE pour les fichiers et dossiers presents a ce niveau de ce dossier
et donc juste un strcompare de noms par rapport au pattern donne?
possiblement en sequencant suivant le nombre de * ds une seule string?)
"** /" is a wildcard that show only directories and their subdirectories
"* /" list only directories presents at this level and nothing else
"*" list everything
a * can be nothing, a str, a single char
wildcards.c

2 -  && et || avec des parenthèses pour les priorités.
(parsing need two commands, even if not checked for access, otherwise gives prompt to write second command
1 || 2 ,exec 2 only if 1 return false(i > 0) "OR_IF"
1 && 2 ,exec 2 only if 1 return true(i == 0) "AND_IF"
So, not pipes, but sequential execution depending on exit(status) of process 1,
they don't seems to communicate directly from 1 to 2,
just keep in memory the exit status until determining of exec 2)
An AND-OR list is a sequence of one or more pipelines separated by the operators "&&" and "||".
Sooooooo, exec will have to do the tests,
but maybe parsing need to determine beginning and end of AND-OR list ?
(struct of str command with an option and a number to say
"this cmd is linked to this command by operator xx"?)
Your shell considers a return value of 0 for true, other positive numbers for false

Need binary tree!
*/
