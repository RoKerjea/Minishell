/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:57:05 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/09 17:47:52 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <signal.h>

typedef struct s_cmd_list
{
	int					type;
	char				**cmd_args;
	char				*redir_in;
	char				*redir_out;
	char				*redir_append;
	char				*heredoc;
	struct s_cmd_list	*next;
}	t_cmd_list;

void	sigint_handler(int sig);
void	sigint_hd_handler(int sig);

#endif
