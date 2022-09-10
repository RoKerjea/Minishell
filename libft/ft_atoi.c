/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:46:17 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/11 00:33:30 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	min;

	i = 0;
	min = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res += str[i] - '0';
		i++;
	}
	if (min == 1)
		res *= -1;
	return (res);
}

/* typedef struct s_atoll
{
	long long	num;
	int			overflow;
}	t_atoll;

t_atoll	ft_atoll(const char *str)
{
	t_atoll	res;
	long long	newres;
	int			i;
	int			min;

	i = 0;
	min = 1;
	res.num = 0;
	res.overflow = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		newres = res.num *10;
		if (newres < res.num)
			return (res);
		res.num = newres;
		res.num += str[i] - '0';
		i++;
	}
	res.num *= min;
	return (res);
} */