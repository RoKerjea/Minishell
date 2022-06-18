/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:21:35 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/18 21:18:44 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	needle;

	needle = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == needle)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == 0 && needle == 0)
		return ((char *)s + i);
	return (0);
}
