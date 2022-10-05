/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:30:26 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/05 21:24:21 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

void	*memset_alloc(int c, size_t len)
{
	void	*point;

	point = malloc(len);
	if (!point)
		return (NULL);
	point = ft_memset(point, c, len);
	return (point);
}
