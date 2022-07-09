/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:21:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 18:02:15 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/macro.h"

// check if char input is a metachar, to be treated differently
int is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	else
		return (NO);
}

// check if char input is a space, to be treated differently
// space, tab, newline and possibly carriage return.
int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (YES);
	else
		return (NO);
}