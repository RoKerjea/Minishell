/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:12:12 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/09 18:44:33 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "common.h"
# include "minishell.h"
# include <sys/types.h>

/* enum e_redir_type
{
	IN,
	OUT,
	APPEND
}; */

enum e_fd_dup_type
{
	READ_END,
	WRITE_END,
	TEMP_READ_END
};

typedef struct s_list_info
{
	unsigned int	size;
	t_parsed_cmd		*head;
	t_parsed_cmd		*tail;
	pid_t			*cpid;
	int				rfds[2];
	int				pfds[3];
	int				status;
}	t_list_info;

// SIMULATE_PARSER_ARGS -> will be deleted
t_parsed_cmd	*create_pipeline(int argc, char *argv[], char *const envp[]);
void		print_cmd_list(t_parsed_cmd *cmd_list);

// envp will be replaced everywhere by t_env
t_list_info	*cmd_list_info(t_parsed_cmd *cmd_list);
void		free_cmd_list(t_parsed_cmd *cmd_list);
int			exec_controller(t_list_info *list_info, t_env *local_env);
int			exec_builtin(char **cmd, char *const envp[]);
int			exec_redirect(t_parsed_cmd *cmd_list, t_list_info *list_info);
void		exec_cmd(char **cmd, char **envp);
void		print_err_open(int errnum, char *path);
void		print_err(int errnum, char *str, int line);
char		**get_paths(char *const envp[]); // to be replaced by t_env
void		free_err_join(char *path, char *tmp, char **paths);
void		free_tab(char **tab);
void		exec_subshell(t_parsed_cmd *cmd, t_list_info *info, char **envp);
void		exec_pipeline(t_parsed_cmd *cmd, t_list_info *info);
int			execute(t_parsed_cmd *cmd, t_list_info *info, t_env *local_env);

#endif
