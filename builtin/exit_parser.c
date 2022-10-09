/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:23:23 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 15:26:31 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_not_num(char *str)
{
	int		i;
	int		j;
	char	*valid_num;

	valid_num = "+-0123456789";
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (valid_num[j] != str[i] && j < 12)
			j++;
		if (j == 12)
			return (1);
		i++;
	}
	return (0);
}

int	is_char_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	count_spaces(const char *str)
{
	int	i;

	i = 0;
	while (is_char_space(str[i]))
		i++;
	return (i);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			i;
	int			min;

	min = 1;
	res = 0;
	i = count_spaces(str);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	res *= min;
	return (res);
}

int	check_overflow(const char *str)
{
	long long	res;
	long long	newres;
	int			i;
	int			min;

	res = 0;
	min = 1;
	i = count_spaces(str);
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			min = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{		
		newres = res * 10;
		if ((newres / 10) != res)
			return (1);
		res = res * 10 + (str[i] - '0') * min;
		if ((res < newres && newres > 0) || (res > newres && newres < 0))
			return (1);
		i++;
	}
	if (str[i] != '\0')
		return (1);
	return (0);
}
