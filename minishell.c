/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/19 11:56:35 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include "./include/macro.h"

int	check_input(char *input)//seems ok, to confirm
{
	int	len;
	int	i;

	len = strlen(input);
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
		{
			i += find_end_quote(input + i, input[i]);
		}
		if (i > len)
			return (NO);
		i++;
	}
	return (YES);
}

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
		if (*input == 0)//J'aime pas :/
			continue;
		if (check_input(input) == NO)//can put next steps inside actions of that if?
		{
			//printerror
			printf("unclosed quotes!\n");
			continue;
		}
		builtin_parser(input, local_env);//ca il faudra le mettre ailleur, mais il marchera pareil
		//list = parser(input, local_env);
		parser(input, local_env);
		//local_env->lst_exit = exec(list, local_env);
	}
	return (0);// return $? i think, maybe not
}

//start of process, get env and ignore args, make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int		status;
	t_env	local_env;

	if (!argc || !argv)
		return (0);
	status = 1;
	printf("gate0\n");// to del
 	if (!env[0])
	{
		printf("gate1\n");// to del
		local_env = minimal_env();
	}
	else 
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