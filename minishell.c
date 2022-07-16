/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/16 17:03:45 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

//start of input loop, should add to history, tokenize->parse->expand->send to exec
int	input(t_env *local_env)
{
	char		*input;
	//t_parsed	*list;

	while (1)//need ttysomething function i think
	{
		input = readline ("cmd>");//history should use this
		printf ("//input== \"%s\"\n", input);//to del
		//check valid input?(quotes?, empty? newline?)
		builtin_parser(input, local_env);//ca il faudra le mettre ailleur, mais il marchera pareil
		//list = parser(input, local_env);
		parser(input, local_env);
		//exec(list, *local_env);
	}
	return (0);// return $? i think
}

//start of process, get env and ignore args, make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int		status;
	t_env	local_env;

	if (!argc || !argv)
		return (0);
	status = 1;
/* 	if (!env)
	{
		update_variable("_=/usr/bin/env", local_env);
		update_variable("SHLVL=1", local_env);
		char	cur_path[PATH_MAX];
		getcwd(cur_path, PATH_MAX);
		update_variable("PWD="cur_path, local_env);
	}
	else */
		local_env = env_list(env);
	//get pwd, shlvl, etc if env = NULL
	//if end, destroy env list,
	printf("Starting Shell\n");// to del
	while (status != 0)
	{
		status = input(&local_env);
	}	
	//free and destroy everything before process end
	return (status);
}