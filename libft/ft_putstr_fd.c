/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:15 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/08 14:14:49 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/utils.h"

int	ft_putstr_fd(const char *str, int fd)
{
	return (write(fd, str, ft_strlen(str)));
}
