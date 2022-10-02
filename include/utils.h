/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:53:56 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/02 16:23:50 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

# define BUFFER_SIZE 32
# define MAX_FD 256

// Print
int		ft_putchar_fd(int c, int fd);
int		ft_putstr_fd(const char *str, int fd);
void	ft_putnbr_fd(int n, int fd);

// Strings
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		ft_isspace_lib(int c);
int		is_only_space(char *str);

// Get line
char	*get_next_line(int fd);

#endif
