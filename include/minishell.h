/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:40:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/07 19:26:13 by rokerjea         ###   ########.fr       */
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
	struct s_env_link	*first;
	struct s_env_link	*last;
}		t_env;

typedef struct s_tok_link
{
	int					meta;
	char				*str;
	struct s_tok_link	*next;
	struct s_tok_link	*prev;
}		t_tok_link;

typedef struct s_tok_list
{
	unsigned int		len;
	struct s_tok_link	*first;
	struct s_tok_link	*last;
}		t_tok_list;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			**ft_freetab(char **tab);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, int j);

//ENV_MAKE.C
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

//TOKENIZER.C
t_tok_list	*tokenizerstart(char *input);
void	print_token(t_tok_list *list);
t_tok_list *make_list();
t_tok_link *make_add_link(t_tok_list *list);
void	sep_token(char *str, t_tok_list *list);

int	strparser(t_tok_list *list, char *str);
int	metaparser(t_tok_list *list, char *str);
int	find_end_quote(char *str, char c);
int	metachar_parser(char *str);
int	meta_and_arg_size(char *str);

int	meta_type(char *str);


//BOOL_STR.C
int	ft_isspace(char c);
int	is_meta(char c);


//TESTS.C
void	print_token(t_tok_list *list);
#endif