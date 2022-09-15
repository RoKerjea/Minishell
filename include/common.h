/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:57:05 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/14 23:48:04 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <signal.h>

/*
enum e_type
{
	BUILTIN,
	CMD,
	FAIL
};*/
/*
typedef struct s_env_link
{
	char				*name;
	char				*variable;
	struct s_env_link	*next;
	struct s_env_link	*prev;
}	t_env_link;

typedef struct s_env
{
	unsigned int		len;
	unsigned int		lst_exit;
	struct s_env_link	*first;
	struct s_env_link	*last;
}	t_env;*/

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

extern int global_var;

void	signal_handler(int signo, siginfo_t *siginfo, void *ucontext);

#endif
