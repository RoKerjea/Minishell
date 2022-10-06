/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:51:10 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/06 17:47:34 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"
#include "../include/utils.h"

t_parsed	*list_parser(t_temp *temp)
{
	t_parsed	*parsed_list;
	t_temp		*temp_next;

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

void	get_cmd_redirection(t_temp *temp, t_parsed_cmd *link)
{
	if (temp->redir_in != NULL)
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
	return ;
}

t_parsed_cmd	*make_parsed_link(t_temp *temp)
{
	t_parsed_cmd	*link;

	link = memset_alloc(0, sizeof(t_parsed_cmd));
	if (!link)
		return (NULL);
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
	get_cmd_redirection(temp, link);
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
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (YES);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (YES);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (YES);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (YES);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (YES);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (YES);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (YES);
	return (NO);
}

char	**empty_tab(void)
{
	char	**res;

	res = malloc(sizeof(char *) * 1);
	if (!res)
		return (res);
	res[0] = NULL;
	return (res);
}

//get str of list of token of similar types in a single char **str
//maybe same function should get fd type list in final link?
//expand, split,unquotes here?NO, only fusion of multiple char** TODO
char	**get_args(t_tok_link *token)
{
	t_tok_link	*token_next;
	char		**res;
	int			i;

	i = 0;
	res = empty_tab();
	if (!res)
		return (NULL);
	while (token != NULL && token->str[0] != NULL)
	{
		token_next = token->next;
		res = char_tab_fuser(res, token->str);
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
	while (token != NULL)
	{
		token = token->next;
		i++;
	}
	return (i);
}
