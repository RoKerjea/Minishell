/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:41:55 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:38:50 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

void	token_sorter(t_tok_link *link, t_temp *temp, t_env *local_env)
{
	if (link->meta == CMD)
		add_token_arg(temp, link);
	else if (link->meta == IN || link->meta == HEREDOC
		|| link->meta == HEREDOC_NOEXPAND)
		temp->type = add_token_in(temp, link, local_env);
	else if (link->meta == OUT || link->meta == APPEND)
		temp->type = add_token_out(temp, link);
}

//get token list and create another list with one link by cmd and every
//redirection in the same link, not expanded or splited yet
t_temp	*temp_sorter(t_tok_list *list, t_env *local_env)
{
	t_tok_link	*link;
	t_tok_link	*nextlink;
	t_temp		*temp;
	t_temp		*tempfirst;

	temp = mktemplist();
	tempfirst = temp;
	link = list->first;
	while (link != NULL)
	{
		nextlink = link->next;
		if (is_not_pipe(link) == YES)
			token_sorter (link, temp, local_env);
		else if (link->meta == PIPE)
		{
			temp->next = mktemplist();
			temp = temp->next;
			destroy_token (link);
		}
		else
			destroy_token (link);
		link = nextlink;
	}
	return (tempfirst);
}

int	add_token_in(t_temp *temp, t_tok_link *link, t_env *local_env)
{
	if (temp->redir_in != NULL)
	{
		if (temp->redir_in->meta == HEREDOC
			|| temp->redir_in->meta == HEREDOC_NOEXPAND)
			if (delete_heredoc_file (temp) == NO)
				return (NO);
		destroy_token(temp->redir_in);
	}
	temp->redir_in = link;
	if (link->meta == HEREDOC || link->meta == HEREDOC_NOEXPAND)
	{
		link->str[0] = heredoc(link, local_env);
		link->meta = HEREDOC;
		return (YES);
	}
	if (access(link->str[0], F_OK) || access(link->str[0], R_OK))
	{
		printerror(link->str[0]);
		return (NO);
	}
	return (YES);
}

//need to do access tests for targets(F_OK, W_OK if F_OK, maybe R_OK??)
int	add_token_out(t_temp *temp, t_tok_link *link)
{
	int	fd;

	if (temp->redir_out != NULL)
		destroy_token(temp->redir_out);
	temp->redir_out = link;
	fd = open(link->str[0], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
	{
		printerror(link->str[0]);
		return (FAIL);
	}
	close (fd);
	return (1);
}
