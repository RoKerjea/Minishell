/*get ac, av, env, heredoc

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
!heredoc a la con: supposed to be done by child process concerned, but only the last one is kept long enough to be used as input





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
*/