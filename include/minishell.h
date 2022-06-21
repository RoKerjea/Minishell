/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:40:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/21 14:47:56 by rokerjea         ###   ########.fr       */
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
	char			*name;
	char			*variable;
	struct s_env_link	*next;
	struct s_env_link	*prev;
}		t_env_link;


typedef struct s_env
{
	unsigned int	len;
	struct s_env_link	*first;
	struct s_env_link	*last;
}		t_env;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			**ft_freetab(char **tab);
char			*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int j);

//ENV.C
t_env	env_list(char **env);
t_env_link	*find_link(char *var_name, t_env *env_list);
void	update_variable(char *name, char *content, t_env *env_list);
void	printenv(t_env *env);
char	*get_env_var(char *name, t_env *env_list);

//DIR.C
void	printpath(void);
int		change_dir(char *str, t_env *env_list);

#endif