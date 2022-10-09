/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:34:18 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:34:58 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"
#include "../include/utils.h"

int	get_type(char **cmd_args)
{
	int	res;

	res = CMD;
	if (!cmd_args)
		return (FAIL);
	if (is_builtins(cmd_args[0]) == YES)
		res = BUILT;
	return (res);
}

int	is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (YES);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (YES);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (YES);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (YES);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (YES);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (YES);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (YES);
	return (NO);
}

int	token_count(t_tok_link *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		token = token->next;
		i++;
	}
	return (i);
}
