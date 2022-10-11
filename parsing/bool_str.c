/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:21:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 14:19:19 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/macro.h"
#include "../include/utils.h"
#include "../include/parsing.h"

// check if char input is a metachar, to be treated differently
int	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	else
		return (NO);
}

// check if char input is a space, to be treated differently
// space, tab, newline and possibly carriage return.
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (YES);
	else
		return (NO);
}

// find & return the length of the str between quotes c
int	find_end_quote(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}
