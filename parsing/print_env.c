/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:10:02 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/18 22:16:14 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printenv(t_env *env)
{
	int	i;
	t_env_link *now;

	i = 0;
	now = env->first;
	while (now)
	{
		printf("%s=%s\n", now->name, now->variable);
		now = now->next;
		i++;
	}
}