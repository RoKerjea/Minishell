/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:30:06 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:31:04 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

char	*ft_strtrim_replace(char *str, char *totrim)
{
	char	*temp;

	if (str == NULL)
		return (str);
	if (ft_strchr(str, ' ') == 0 && ft_strchr(str, '<') == 0
		&& ft_strchr(str, '>') == 0)
		return (str);
	temp = ft_strtrim(str, totrim);
	free (str);
	str = temp;
	return (str);
}
