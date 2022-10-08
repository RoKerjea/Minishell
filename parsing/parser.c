/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:19 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/08 20:01:32 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

/*
BUT : Fournir une liste chainee avec des cmds fixes pour les commandes
et un type en int defini en macro pour builtin or exec*/

//after parser is finished, only env, parsed list, parsedlinks and
t_parsed	*parser(char *input, t_env *local_env)
{
	t_temp		*temp;
	t_parsed	*parsed_list;
	t_tok_list	*list;

	list = tokenizerstart(input);//this step should be locked and perfect!!
	if (list == NULL)
		return (NULL);
	//print_token(list);
	token_expander(list, local_env); //this step done(except protection...)
	/* print_token(list);
	printf ("\033[1;31mgate before splitter after expander\n\033[0m"); */
	if (token_splitter(list) == NO)
	{
		destroy_token_list(list);
		return (NULL);
	}
	/*print_token(list);
  	printf ("\033[1;31mgate before unquoter after splitter\n\033[0m"); */
	unquoter_loop(list);
	temp = temp_sorter(list, local_env);
	free (list);
	parsed_list = list_parser(temp);
	//print_parsed_list(parsed_list->first);
	if (check_parsed_cmd(parsed_list) == NO)
		destroy_final_list(parsed_list);
	//print_parsed_list(parsed_list->first);
	return (parsed_list);
}

int	check_parsed_cmd(t_parsed *parsed_list)
{
	t_parsed_cmd	*cmd;
	t_parsed_cmd	*cmd_next;

	if (!parsed_list)
		return (NO);
	cmd = parsed_list->first;
	if ((cmd->cmd_args == NULL || cmd->cmd_args[0] == NULL 
			|| cmd->cmd_args[0][0] == '\0') && cmd->next == NULL)
		return (NO);
	while (cmd != NULL)
	{
		cmd_next = cmd->next;
		if (cmd->exec_type == FAIL)
			return (NO);
		cmd = cmd_next;
	}	
	return (YES);
}

void	destroy_final_list(t_parsed *parsed_list)//to use in exec actuall y
{
	t_parsed_cmd	*cmd;
	t_parsed_cmd	*cmd_next;

	cmd = parsed_list->first;
	while (cmd != NULL)
	{
		cmd_next = cmd->next;
		ft_freetab(cmd->cmd_args);
		if (cmd->redir_in)
			free(cmd->redir_in);
		if (cmd->heredoc)
		{
			unlink(cmd->heredoc);
			free(cmd->heredoc);
		}
		if (cmd->redir_out)
			free(cmd->redir_out);
		if (cmd->redir_append)
			free(cmd->redir_append);
		free (cmd);
		cmd = cmd_next;
	}
	parsed_list->len = 0;
	return ;
}
