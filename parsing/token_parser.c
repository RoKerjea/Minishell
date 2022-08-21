/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:42:10 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/21 17:15:00 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/macro.h"

char	*redir_trimmer(char	*str, int i)
{
	char	*temp;
	temp = str;
	str = ft_strdup(str + i);
	free (temp);
	return (str);
}

// identify the type of redirection the current token is
enum	e_type	meta_type(char *str)
{
	if (strncmp(str, "<<", 2) == 0)
	{
		if (strchr(str, '\'') != 0)
			return (HEREDOC_NOEXPAND);
		return (HEREDOC);
	}
	if (strncmp(str, "<", 1) == 0)
		return (IN);
	if (strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (strncmp(str, ">", 1) == 0)
		return (OUT);
	if (strncmp(str, "|", 1) == 0)
		return (PIPE);
	else
		return (CMD);
}

// fnd & return the length of meta token, from the metachar,
// to the end of it's arg, if any
int	metachar_parser(char *str)
{
	if (strncmp(str, "<<", 2) == 0 || strncmp(str, ">>", 2) == 0)
		return (meta_and_arg_size(str + 2) + 2);
	if (strncmp(str, "<", 1) == 0 || strncmp(str, ">", 1) == 0)
		return (meta_and_arg_size(str + 1) + 1);
	if (strncmp(str, "|", 1) == 0)
		return (1);
	else
		return (0);
}

// find & return the length of arg of redirection token
int	meta_and_arg_size(char *str) // could be fused later with str parser?
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) == YES && str[i] != '\0')
		i++;
	while (is_meta(str[i]) == NO && ft_isspace(str[i]) == NO && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i, str[i]);
		else
			i++;
	}
	return (i);
}
