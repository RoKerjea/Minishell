/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 05:37:21 by nvasilev          #+#    #+#             */
/*   Updated: 2022/10/02 16:23:36 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace_lib(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (c);
	return (0);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace_lib(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
