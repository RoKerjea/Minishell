/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assign_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:37:44 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:39:54 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

int	is_not_pipe(t_tok_link *link)
{
	if (link->meta == CMD || link->meta == IN || link->meta == HEREDOC
		|| link->meta == HEREDOC_NOEXPAND || link->meta == OUT
		|| link->meta == APPEND)
		return (YES);
	return (NO);
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
