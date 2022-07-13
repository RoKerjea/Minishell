/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:41:55 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/13 12:11:11 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

/* typedef struct s_temp
{
	t_tok_link	*cmd_list_first;
	t_tok_link	*cmd_list_last;
	t_tok_link	*in_list_first;
	t_tok_link	*in_list_last;
	t_tok_link	*out_list_first;
	t_tok_link	*out_list_last;
	t_temp		*next;
}	t_temp; */

//I don't really need to keep all the redirections tokens if i can just test
//them immediatly and replace the previous one with the last one done??
//PB, heredoc need to be done by at that step and kept as a temp file to give to exec??

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
			//update_next_token(temp);
			temp->next = mktemplist();
			temp = temp->next;
		}
		link = link->next;
		link->prev->next = NULL;
	}
	return (tempfirst);
}

//TODO needed ft
t_temp	*mktemplist(void)
{
	t_temp	*temp_link;	

	temp_link = malloc(sizeof(t_temp));
	temp_link->cmd_list_first = NULL;
	temp_link->cmd_list_last = NULL;
	temp_link->in_list_first = NULL;
	temp_link->in_list_last = NULL;
	temp_link->out_list_first = NULL;
	temp_link->out_list_last = NULL;
	temp_link->next = NULL;
	return(temp_link);
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

