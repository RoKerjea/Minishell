/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:41:55 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/06 19:27:40 by rokerjea         ###   ########.fr       */
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

int	is_not_pipe(t_tok_link *link)
{
	if (link->meta == CMD || link->meta == IN || link->meta == HEREDOC
		|| link->meta == HEREDOC_NOEXPAND || link->meta == OUT
		|| link->meta == APPEND)
		return (YES);
	return (NO);
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

t_temp	*mktemplist(void)
{
	t_temp	*temp_link;	

	temp_link = memset_alloc (0, sizeof(t_temp));
	if (!temp_link)
		return (NULL);
	temp_link->type = 1;
	return (temp_link);
}

void	add_token_arg(t_temp *temp, t_tok_link *link)
{
	if (temp->cmd_list_first == NULL)
		temp->cmd_list_first = link;
	if (temp->cmd_list_last != NULL)
		temp->cmd_list_last->next = link;
	temp->cmd_list_last = link;
	temp->cmd_list_last->next = NULL;
}

void	printerror(char *prob)
{
	write(2, "minishell: ", 11);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	if (prob)
	{
		write(2, ": ", 2);
		write(2, prob, ft_strlen(prob));
	}
	write(2, "\n", 1);
}

int	delete_heredoc_file(t_temp *temp)
{
	int	fd;

	fd = open(temp->redir_in->str[0], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NO);
	unlink (temp->redir_in->str[0]);
	close (fd);
	return (YES);
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
