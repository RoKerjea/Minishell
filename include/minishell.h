/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:40:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/17 19:22:40 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <errno.h>

//only builtins and env maker need those structures
typedef struct s_env_link
{
	char				*name;
	char				*variable;
	struct s_env_link	*next;
	struct s_env_link	*prev;
}		t_env_link;

typedef struct s_env//maybe one more int for $?, the exit status of last command done?
{
	unsigned int		len;
	unsigned int		lst_exit;
	struct s_env_link	*first;
	struct s_env_link	*last;
}		t_env;

typedef struct s_parsed_cmd//new version
{
	int					exec_type;//defined in macro
	char				**cmd_args;//for execve, arg[0] sera la cmd dont trouver le path, ou dont le path sera donne
	char				*redir_in;
	char				*heredoc;
	char				*redir_out;
	char				*redir_append;
	struct s_parsed_cmd	*next;
}	t_parsed_cmd;

typedef struct s_parsed
{
	unsigned int	len;
	t_parsed_cmd	*first;
	t_parsed_cmd	*last;
}		t_parsed;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			**ft_freetab(char **tab);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, int j);

//ENV_MAKE.C
t_env			minimal_env(void);
t_env			env_list(char **env);
t_env_link		*create_link(char *envstr);
void			split_env(char *str, t_env_link *link);
void			forgelink(t_env_link *prev, t_env_link *now);

//ENV_USE.C
void			printenv(t_env *env);
void			update_variable(char *str, t_env *env_list);
void			remove_variable(char *str, t_env *env_list);
t_env_link		*find_link(char *var_name, t_env *env_list);
char			*get_env_var(char *name, t_env *env_list);

//DIR.C
void			printpath(void);
int				change_dir(char *str, t_env *env_list);

//PARSER.C
t_parsed	*parser(char *input, t_env *local_env);

//BUILTINS.C
void	builtin_parser(char *input, t_env *local_env);


int	find_end_quote(char *str, char c);

#endif