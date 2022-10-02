/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:41:55 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/02 18:42:36 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

//I don't really need to keep all the redirections tokens if i can just test
//them immediatly and replace the previous one with the last one done??
//PB, heredoc need to be done by at that step and kept as a temp file to give to exec??

//get token list and create another list with one link by cmd and every
//redirection in the same link, not expanded or splited yet
//need to react to redirection error, stop and free everything for current command, et find next pipe before continuing
t_temp	*token_sorter(t_tok_list *list, t_env *local_env)
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
		if (link->meta == CMD)
			add_token_arg(temp, link);
		else if (link->meta == IN || link->meta == HEREDOC || link->meta == HEREDOC_NOEXPAND)
			temp->type = add_token_in(temp, link, local_env);
		else if (link->meta == OUT || link->meta == APPEND)
			temp->type = add_token_out(temp, link);
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

	temp_link = malloc(sizeof(t_temp));
	//protect
	temp_link->type = 1;
	temp_link->cmd_list_first = NULL;
	temp_link->cmd_list_last = NULL;
	temp_link->redir_in = NULL;
	temp_link->redir_out = NULL;
	temp_link->next = NULL;
	return (temp_link);
}

void	add_token_arg(t_temp *temp, t_tok_link *link)
{
	if (temp->cmd_list_first == NULL)
		temp->cmd_list_first = link;
	if (temp->cmd_list_last != NULL)
		temp->cmd_list_last->next = link;/* 
	printf("inputin sorter = \n");
	print_char_tab(link->str);*/
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

//Maybe do the redirections tests here?(then expander must be done just before it!!)
//need to do the open tests here, and replace previous redir with new one
//print "minishell: (target): No such file or directory" on error fd
int	add_token_in(t_temp *temp, t_tok_link *link, t_env *local_env)
{
	if (temp->redir_in != NULL)
	{
		int	fd;
		if (temp->redir_in->meta == HEREDOC || temp->redir_in->meta == HEREDOC)
		{
			fd = open(temp->redir_in->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			unlink (temp->redir_in->str[0]);
			close (fd);
		}
		destroy_token(temp->redir_in);	
	}
	temp->redir_in = link;
	if (link->meta == HEREDOC || link->meta == HEREDOC_NOEXPAND)
	{
		link->str[0] = heredoc(link, local_env);
		link->meta = HEREDOC;
		return (1);
	}
	if (access(link->str[0], F_OK))
	{
		printerror(link->str[0]);
		return (FAIL);
	}
	if (access(link->str[0], R_OK))//need W_OK too?
	{
		printerror(link->str[0]);
		return (FAIL);
	}
	return (1);
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
