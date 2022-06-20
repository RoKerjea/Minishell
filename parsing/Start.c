/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:47:11 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/20 17:29:52 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_parser(char *input, t_env *local_env)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		exit (0);//exit value should be unsigned int specified after string "exit" (0 -> 255)
	if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		printenv(local_env);
	if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
		printpath();
	if (ft_strncmp(input, "cd", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
		change_dir(input, local_env);
	if (ft_strncmp(input, "export ", 7) == 0 && (input[8] != ' ' || input[8] != '\0'))
		new_link(input + 7, local_env);
}

int	input(t_env *local_env)
{
	char *input;
	
	while (1)
	{
		input = readline ("cmd>");
		printf ("//input== \"%s\"\n", input);//to del
		builtin_parser(input, local_env);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (!argc || !argv || !env)
		return (0);
	int	status;
	t_env local_env;
	
	status = 1;	
	local_env = env_list(env);
	//copy env to chained list so it can be edited later
	//if end, destroy env list,
	printf("Starting Shell\n");// to del
	while (status != 0)
	{
		status = input(&local_env);
	}
	//free and destroy everything before process end
	return (status);
}