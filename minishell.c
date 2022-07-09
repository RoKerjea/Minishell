/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 17:39:09 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

//start of input loop, should add to history, tokenize->parse->expand->send to exec
int	input(t_env *local_env)
{
	char		*input;
	t_tok_list	*list;

	while (1)//need ttysomething function i think
	{
		input = readline ("cmd>");//history should use this
		printf ("//input== \"%s\"\n", input);//to del
		builtin_parser(input, local_env);//ca il faudra le mettre ailleur, mais il marchera pareil
		list = tokenizerstart(input);
		print_token(list);
		//parser(list, local_env)
		//print_parsed_list;
	}
	return (0);// return $? i think
}

//start of process, get env and ignore args, make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int		status;
	t_env	local_env;

	if (!argc || !argv || !env)
		return (0);
	status = 1;
	local_env = env_list(env);
	//if end, destroy env list,
	printf("Starting Shell\n");// to del
	while (status != 0)
	{
		status = input(&local_env);
	}	
	//free and destroy everything before process end
	return (status);
}