/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:40:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/08 14:17:08 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>

//only builtins and env maker need those structures
//need next AND prev because if i remove one, i need to link next and prev to each other
typedef struct s_env_link
{
	char				*name;
	char				*variable;
	struct s_env_link	*next;
	struct s_env_link	*prev;
}		t_env_link;

typedef struct s_env
{
	unsigned int		len;
	unsigned int		lst_exit;
	//harcoded $PATH in case of env -i
	struct s_env_link	*first;
	struct s_env_link	*last;
}		t_env;

typedef struct s_parsed_cmd
{
	int					exec_type;
	char				**cmd_args;
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

//LIBFT
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			**ft_freetab(char **tab);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, int j);
int				ft_atoi(const char *str);
char			*ft_strtrim(char const *s1, char const *set);

//ENV_MAKE.C
int	env_destroy_list(t_env *env_list);
int	env_destroy_link(t_env_link *link);
t_env			*minimal_env(void);
t_env			*env_list(char **env);
t_env_link		*create_link(char *envstr);
void			split_env(char *str, t_env_link *link);
void			forgelink(t_env_link *prev, t_env_link *now);

//ENV_USE.C
char			**make_env_tab(t_env *env);
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
int	builtin_parser(char **input, t_env *local_env);


int	find_end_quote(char *str, char c);


//TODELETE
void	print_parsed_list(t_parsed_cmd *final_link);
void	destroy_final_list(t_parsed *parsed_list);
#endif