/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:40:57 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/18 22:40:47 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>


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

//ENV.C
t_env	env_list(char **env);

void	printenv(t_env *env);
#endif