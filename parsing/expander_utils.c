/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:09:47 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 14:00:43 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

char	*get_right_str(char	*str)
{
	str += wordlen(str);
	return (ft_strdup(str));
}

char	*extract_name(char *str)
{
	char	*name;
	int		i;

	i = wordlen(str);
	name = ft_strndup(str + 1, i - 1);
	return (name);
}

int	wordlen(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[i]))
		return (i + 1);
	while (str[i] != 36 && str[i] != '\0' && ft_isspace(str[i]) == NO
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '/' && str[i] != '='
		&& str[i - 1] != '?')
		i++;
	return (i);
}
