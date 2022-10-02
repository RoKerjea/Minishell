/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:19 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/02 19:31:43 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

/*
BUT : Fournir une liste chainee avec des cmds fixes pour les commandes et un type en int defini en macro pour builtin or exec
list of tokens with type and *str separe, les espaces ignores si ils sont a l'exterieur de quotes,
les metachars dans leurs str* a part(si pas inside quotes)*/

//after parser is finished, only env, parsed list, parsedlinks and
t_parsed	*parser(char *input, t_env *local_env)
{
	t_temp		*temp;
	t_parsed	*parsed_list;
	t_tok_list	*list;
	
	list = tokenizerstart(input);//this step should be locked and perfect!!
	if (list == NULL)
		return (NULL);
	/* print_token(list); */

	token_expander(list, local_env); //this step should be done(except protection...)
	
  /*  	print_token(list);
	printf ("\033[1;31mgate before splitter after expander\n\033[0m"); */
	
	if (token_splitter(list) == NO)
	{
		destroy_token_list(list);
		return (NULL);
	}
	
  	/* print_token(list);
  	printf ("\033[1;31mgate before unquoter after splitter\n\033[0m"); */
	
	unquoter_loop(list);
	temp = token_sorter(list, local_env);
	free (list);
	parsed_list = list_parser(temp);
	//print_parsed_list(parsed_list->first);
	if (check_parsed_cmd(parsed_list) == NO)
		destroy_final_list(parsed_list);
	return (parsed_list);
}

int	check_parsed_cmd(t_parsed *parsed_list)
{
	t_parsed_cmd	*cmd;
	t_parsed_cmd	*cmd_next;
	
	if (!parsed_list)
		return (NO);
	cmd = parsed_list->first;
	while (cmd != NULL)
	{
		cmd_next = cmd->next;
		if (cmd->cmd_args == NULL || cmd->cmd_args[0] == NULL
			|| cmd->cmd_args[0][0] == '\0')
			return (NO);
		if (cmd->exec_type == FAIL)
			return (NO);
		cmd = cmd_next;
	}	
	return (YES);
}

void	destroy_final_list(t_parsed *parsed_list)//to use in exec actually
{
	t_parsed_cmd *cmd;
	t_parsed_cmd *cmd_next;
	
	cmd = parsed_list->first;
	while (cmd != NULL)
	{
		cmd_next = cmd->next;
		ft_freetab(cmd->cmd_args);
		if (cmd->redir_in)
			free(cmd->redir_in);
		if (cmd->heredoc)
			free(cmd->heredoc);
		if (cmd->redir_out)
			free(cmd->redir_out);
		if (cmd->redir_append)
			free(cmd->redir_append);
		free (cmd);
		cmd = cmd_next;
	}
	parsed_list->len = 0;
	return;
}

t_parsed	*list_parser(t_temp *temp)
{
	t_parsed *parsed_list;
	t_temp *temp_next;

	parsed_list = malloc(sizeof(t_parsed));
	temp_next = temp->next;
	parsed_list->len = 1;
	parsed_list->first = make_parsed_link(temp);
	parsed_list->last = parsed_list->first;
	free (temp);
	temp = temp_next;
	while (temp != NULL)
	{
		temp_next = temp->next;
		parsed_list->last->next = make_parsed_link(temp);
		parsed_list->last = parsed_list->last->next;
		parsed_list->len++;
		free (temp);
		temp = temp_next;
	}
	return (parsed_list);
}

//make final parsed link from temp link, with all args expanded and separated,
//exterior quotes removed, nothing more should be needed for this link/CMD

//!neeed a complete step of redirection parsing and only returning one for in and out at maximum
t_parsed_cmd	*make_parsed_link(t_temp *temp)
{
	t_parsed_cmd	*link;

	link = malloc(sizeof(t_parsed_cmd));
	//prot
	//memset (link, 0, sizeof(t_parsed_cmd))
	if (temp->cmd_list_first == NULL || temp->type == 0)
	{
		link->cmd_args = NULL;
		link->exec_type = FAIL;
	}
	else
	{
		link->cmd_args = get_args(temp->cmd_list_first);
		link->exec_type = get_type(link->cmd_args);
	}
	//can delete next 4 lines if memset link
	link->redir_in = NULL;
	link->heredoc = NULL;
	link->redir_out = NULL;
	link->redir_append = NULL;
	if (temp->redir_in != NULL)//can externalize in subfunctions
	{
		if (temp->redir_in->meta == IN)
			link->redir_in = ft_strdup(temp->redir_in->str[0]);
		if (temp->redir_in->meta == HEREDOC)
			link->heredoc = ft_strdup(temp->redir_in->str[0]);
		destroy_token(temp->redir_in);
	}
	if (temp->redir_out != NULL)
	{
		if (temp->redir_out->meta == OUT)
			link->redir_out = ft_strdup(temp->redir_out->str[0]);
		if (temp->redir_out->meta == APPEND)
			link->redir_append = ft_strdup(temp->redir_out->str[0]);
		destroy_token(temp->redir_out);
	}
	link->next = NULL;
	return (link);
}

int	get_type(char **cmd_args)
{
	int	res;

	res = CMD;
	if (!cmd_args)
		return (FAIL);
	if (is_builtins(cmd_args[0]) == YES)
		res = BUILT;
	return (res);
}

//can transform cmd[x + 1] == sep with ft_isspace(cmd[x+1])??
//can probably use a lookup table here too
int	is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "exit", 5) == 0 && (cmd[4] == ' ' || cmd[4] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "env", 4) == 0 && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "pwd", 4) == 0 && (cmd[3] == ' ' || cmd[3] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "cd", 3) == 0 && (cmd[2] == ' ' || cmd[2] == '\0'))
		return (YES);
	if (ft_strncmp(cmd, "export", 7) == 0 && (cmd[7] != ' ' || cmd[7] != '\0'))
		return (YES);
	if (ft_strncmp(cmd, "unset", 6) == 0 && (cmd[6] != ' ' || cmd[6] != '\0'))
		return (YES);
	return (NO);
}

char	**empty_tab(void)
{
	char	**res;

	res = malloc(sizeof(char*) * 1);
	if (!res)
		return (res);
	res[0] = NULL;
	return(res);
}

//get str of list of token of similar types in a single char **str
//maybe same function should get fd type list in final link?
//expand, split,unquotes here?NO, only fusion of multiple char** TODO
char	**get_args(t_tok_link *token)
{
	t_tok_link	*token_next;
	char	**res;
	int		i;
	
	i = 0;
	res = empty_tab();
	if (!res)
		return (NULL);
	while (token != NULL && token->str[0] != NULL)
	{
		token_next = token->next;
		res = char_tab_fuser(res, token->str);
/* 		if (!res)
			return (NULL); */ //can probably let while continue to destroy tokens and still return NULL in the end
		i++;
		destroy_token(token);
		token = token_next;
	}
	return (res);
}

int	token_count(t_tok_link *token)
{
	int	i;

	i = 0;
	while(token != NULL)
	{
		token = token->next;
		i++;
	}
	return(i);
}
