/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:19 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/13 13:34:39 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

/*
BUT : Fournir une liste chainee avec des cmds fixes pour les commandes et un type en int defini en macro pour builtin or exec
list of tokens with type and *str separe, les espaces ignores si ils sont a l'exterieur de quotes,
les metachars dans leurs str* a part(si pas inside quotes)

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

//after parser is finished, only ennv, parsed list, parsedlinks and
t_parsed	*parser(char *input, t_env *local_env)
{
	t_temp		*temp;
	//t_parsed	*parsed_list;
	t_tok_list	*list;
	(void)local_env;
	
	list = tokenizerstart(input);
	print_token(list);
	//expander replace in every str in every link of list
	//bash: $TEST: ambiguous redirect if TEST="file1 file2"
	//means parse step after expander wich is after tokenizer
	//token_expander(list, local_env);
	printf ("gate0\n");
	temp = token_sorter(list);
	print_temp_list(temp);
	//test redirections somewhere here??
	//parsed_list = list_parser(temp);
	//return (parsed_list);
	return (NULL);
}
/* 
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
		parsed_list->last = parsed_list->last->next;
		parsed_list->len++;
	}
	return (parsed_list);
} */

//make final parsed link from temp link, with all args expanded and separated,
//exterior quotes removed, nothing more should be needed for this link/CMD

//!neeed a complete step of redirection parsing and only returning one for in and out at maximum
/* t_parsed_cmd	*make_parsed_link(t_temp *temp)
{
	t_parsed_cmd	*link;

	link = malloc(sizeof(t_parsed_cmd));
	//prot
	link->cmd_args = get_args(temp->cmd_list_first);
	link->exec_type = get_type(temp->cmd_list_first);
 	link->fdins_args = get_args(temp->in_list_first);
	link->fdins = redir_types(temp->in_list_first);
	link->fdouts_args = get_args(temp->out_list_first);
	link->fdouts = redir_types(temp->out_list_first);
	link->next = NULL;
	return (link);
} */

/* int	*redir_types(t_tok_link *token)
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
} */
/* 
int	get_type(char **cmd_args)
{
	int	res;

	res = CMD;
	if (is_builtins(cmd_args[0]) == YES)
		res = BUILT;
	return (res);
} */

//can transform cmd[x + 1] == sep with ft_isspace(cmd[x+1])??
/* int	is_builtins(char *cmd)
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
} */

//get str of list of token of similar types in a single char **str
//maybe same function should get fd type list in final link?
/* char	**get_args(t_tok_link *token)
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
} */

/* int	token_count(t_tok_link *token)
{
	int	i;

	i = 0;
	while(link != NULL)
	{
		token = token->next;
		i++;
	}
	return(i);
} */
/*
how to deal with exterior quotes? "str" => str
' ' are str separators
*/