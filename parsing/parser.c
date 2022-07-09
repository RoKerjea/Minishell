/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:19 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 18:09:37 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"

typedef struct s_parsed_cmd
{
	int					exec_type;
	char				**cmd_args;//for execve
	int					*redir_in;
	char				**redir_in_target;
	int					*redir_out;
	char				**redir_out_target;
	struct s_parsed_cmd	*next;
}	t_parsed_list;

typedef struct s_parsed_link
{
	int						*type;//defini en MACRO avec un int pour CMD, BUILTIN
	char					**cmd_args;//pour les arguments et options(args[0] SHOULD be the cmd name, by convention)
	int						*fdins;//list de fdin pour la cmd, avec seulement la derniere a utiliser(2, 3, 4 ou rien) but need to open and close all others...
	char					**fdins_args;//cible des redirections correspondantes a leurs fdins...
	int						*fdouts;// (2, 5, 6 ou rien)
	char					**fdouts_args;//cibles si il y a
	struct s_parsed_link	*next;//if NULL, first cmd, if not NULL, pipe fdin exist but maybe not used for this cmd
	struct s_parsed_link	*prev;//if NULL, last cmd, if both NULL, only one cmd, so no pipe, and no fork for builtins
}		t_parsed_link;

/*Need to talk with nikita about format, because it might be simpler to use this structure\/ rather than ^
typedef struct s_parsed_link
{
	int						*type;//defini en MACRO avec un int pour CMD, BUILTIN
	char					**cmd_args;//pour les arguments et options(args[0] SHOULD be the cmd name, by convention)
	struct s_redirection	*redir_in_list;//list de fdin pour la cmd, avec seulement la derniere a utiliser(2, 3, 4 ou rien) but need to open and close all others...
	struct s_redirection	*redir_out_list;
	struct s_parsed_link	*next;//if NULL, first cmd, if not NULL, pipe fdin exist but maybe not used for this cmd
	struct s_parsed_link	*prev;//if NULL, last cmd, if both NULL, only one cmd, so no pipe, and no fork for builtins
}		t_parsed_link;
*/
typedef struct s_redirection
{
	int						type; //2, 3, 4, 5, 6 ou rien (pour stdin/stdout) en MACRO
	char					*target; //cible correspondante;
}	t_redirection;

typedef struct s_parsed
{
	unsigned int			len;
	struct s_parsed_link	*first;
	struct s_parsed_link	*last;
}		t_parsed;

t_tok_link	*link;
t_tok_list	*list;

/*
BUT : Fournir une liste chainee avec des cmds fixes pour les commandes et un type en int defini en macro pour builtin or exec
list of tokens with type and *str separe, les espaces ignores si ils sont a l'exterieur de quotes,
les metachars dans leurs str* a part(si pas inside quotes)

HOW: Make a link by command, adding in and out as params, until find pipe | or end of list?
can be used to get args after redir all in one link
only need to get redirections in order from left to right and use the last one
maybe split spaces for args of cmd(optional for now)
temp struct to store various variable?
until | or NULL
if 3 or 4, in fdin redir
if 5 or 6 , in fdout redir
if 1, to cmd, one by one
once finished, find builtins for types
if a field cmd is empty, errors
if redir empty, either pipe or stdandartfd, depending if first/last link(prev ==NULL) or not
need to test redir of multiple args if args come from $VAR(var="arg1 arg2")
expander cycle on every str, then split for cmd args?
what if cmd is in $VAR? then expand first and then char *cmd and char **args(but what if VAR should be splitted in redir? ignore, multi redir?)
*/

typedef struct s_temp
{
	t_tok_link	*cmd_list_first;
	t_tok_link	*cmd_list_last;
	t_tok_link	*in_list_first;
	t_tok_link	*in_list_last;
	t_tok_link	*out_list_first;
	t_tok_link	*out_list_last;
	t_temp		*next;

}	t_temp;

//get token list and create another list with one link by cmd and every
//redirection in the same link, not expanded or splited yet
t_temp	*token_sorter(t_tok_list	*list)
{
	t_tok_link	*link;
	t_temp		*temp;
	t_temp		*tempfirst;
	
	temp = mktemplist();
	tempfirst = temp;
	link = list->first;
	while (link != NULL)
	{
		if (link->meta == CMD)
			add_token(temp, link, 1);
		if (link->meta == IN || link->meta == HEREDOC)
			add_token(temp, link, 2);
		if (link->meta == OUT || link->meta == APPEND)
			add_token(temp, link, 3);
		if (link->meta == PIPE)
		{
			update_next_tokens(temp);
			temp->next = mktemplist();
			temp = temp->next;
		}
		link = link->next;
		link->prev->next = NULL;
	}
	return (tempfirst);
}

void	add_token(t_temp *temp, t_tok_link *link, int type)
{
	t_tok_link	*var_start;
	t_tok_link	*var_last;
	
	if (type == 1)
	{
		var_start = temp->cmd_list_first;
		var_last = temp->cmd_list_last;
	}
	if (type == 2)
	{
		var_start = temp->in_list_first;
		var_last = temp->in_list_last;
	}
	if (type == 3)
	{
		var_start = temp->out_list_first;
		var_last = temp->out_list_last;
	}
	if(var_start == NULL)
		var_start = link;
	var_last->next = link;
	link->prev = var_last;
	var_last = link;
}

t_parsed	*make_parsed_list(t_temp *temp)
{
	t_parsed		*list;
	t_parsed_link	*link;

	list = malloc (sizeof(t_parsed));
	link = make_parsed_link(temp);
	list->first = link;
	temp = temp->next;
	while (temp != NULL)
	{
		link->next = make_parsed_link(temp);
		link->next->prev = link;
		link = link->next;
		temp = temp->next;
	}
	list->last = link;
	return (list);
}

t_parsed	*parser(t_tok_list	*list, t_env *local_env)
{
	t_temp		*temp;
	t_parsed	*parsed_list;

	//print_token(list);
	//expander replace in every str in every link of list
	//bash: $TEST: ambiguous redirect if TEST="file1 file2"
	//means parse step after expander wich is after tokenizer
	token_expander(list, local_env);
	temp = token_sorter(list);
	parsed_list = list_parser(temp);
	return (parsed_list);
}

t_parsed	*list_parser(t_temp *temp)
{
	t_parsed *parsed_list;

	parsed_list = malloc(sizeof(t_parsed));
	parsed_list->len = 1;
	parsed_list->first = make_parsed_link(temp);
	parsed_list->last = parsed_list->first;
	temp = temp->next;
	while (temp != NULL)
	{
		parsed_list->last->next = make_parsed_link(temp);
		parsed_list->last->next->prev = parsed_list->last;
		parsed_list->last = parsed_list->last->next;
		parsed_list->len++;
	}
	return (parsed_list);
}

//make final parsed link from temp link, with all args expanded and separated,
//exterior quotes removed, nothing more should be needed for this link/CMD
t_parsed_link	*make_parsed_link(t_temp *temp)
{
	t_parsed_link	*link;

	link = malloc(sizeof(t_parsed_link));
	//prot
	link->cmd_args = get_args(temp->cmd_list_first);
	link->type = get_type(temp->cmd_list_first);
	link->fdins_args = get_args(temp->in_list_first);
	link->fdins = redir_types(temp->in_list_first);
	link->fdouts_args = get_args(temp->out_list_first);
	link->fdouts = redir_types(temp->out_list_first);
	link->next = NULL;
	link->prev = NULL;
	return (link);
}

int	*redir_types(t_tok_link *token)
{
	int	*res;
	int	i;

	i = 0;
	res = malloc(sizeof(int) * (token_count(token) + 1));
	while (token != NULL)
	{
		res[i] = token->meta;
		i++;
	}
}

int	get_type(char **cmd_args)
{
	int	res;

	res = CMD;
	if (is_builtins(cmd_args[0]) == YES)
		res = BUILT;
	return (res);
}


//can transform cmd[x + 1] == sep with ft_isspace(cmd[x+1])??
int	is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "exit", 4) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "env", 3) == 0 && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "cd", 2) == 0 && (cmd[2] == ' ' || cmd[2] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "export", 6) == 0 && (cmd[7] != ' ' || cmd[7] != '\0'))
		return (YES);
	if (ft_strncmp(cmd, "unset", 5) == 0 && (cmd[6] != ' ' || cmd[6] != '\0'))
		return (YES);
	return (NO);
}

//get str of list of token of similar types in a single char **str
//maybe same function should get fd type list in final link?
char	**get_args(t_tok_link *token)
{
	char	**res;
	int		num;
	int		i;
	
	i = 0;
	num = token_count(token);
	res = malloc (sizeof(char *) * (num + 1));
	//prot
	while (i < num)//can get rid of num
	{
		res[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	res [i] == NULL;
	return (res);
}

int	token_count(t_tok_link *token)
{
	int	i;

	i = 0;
	while(link != NULL)
	{
		token = token->next;
		i++;
	}
	return(i);
}
/*
cmd is arg[0] in char **arg!
how to deal with exterior quotes? "str" => str
' ' are str separators

/*
ls <in -l <in2 -a
est valide en tant que "ls -l -a" avec deux redir in!!
*/