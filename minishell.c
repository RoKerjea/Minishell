/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:46 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/30 18:23:21 by rokerjea         ###   ########.fr       */
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
	char		**input;
	t_parsed	*list;

	input = malloc(sizeof(char *) * 2);
	input[1] = 0;
	while (1)//need ttysomething function i think
	{
		input[0] = ft_strdup("truc <in1 machin $PAGER <in2 >out1 | chose");
		//input[0] = readline ("cmd>");//history should use this
		printf ("//input== \"%s\"\n", input[0]);//to del
		//check valid input?(quotes?, empty? newline?)
		if (input[0] == NULL || input[0][0] == '\0')//J'aime pas :/
		{
			printf("no input!\n");
			continue ;//peux virer les continue si je fais une fonction check input qui fait les deux if avec des returns!!
		}
		//add_history (input[0]);
		if (check_input(input[0]) == NO)//can put next steps inside actions of that if?
		{
			//printerror
			printf("unclosed quotes!\n");
			continue ;
		}
		builtin_parser(input, local_env);//ca il faudra le mettre ailleur, mais il marchera pareil
		list = parser(input[0], local_env);
		printf("\033[1;31m");
		printf ("res at end of parsing =>\n");
		printf("\033[0m");
		print_parsed_list(list->first);
		free(input[0]);
		free(input);
		env_destroy_list(local_env);
		destroy_final_list(list);
		exit (0);
		//destroy_env_input_list(list, input, local_env);
		//parser(input[0], local_env);
		(void)list;
		//local_env->lst_exit = exec(list, local_env);
	}
	return (0);// return $? i think, maybe not
}

//start of process, get env and ignore args, make internal env and launch input loop
int	main(int argc, char **argv, char **env)
{
	int		status;
	t_env	*local_env;

	if (!argc || !argv)
		return (0);
	status = 1;
	if (!env[0])
	{
		local_env = minimal_env();
	}
	else
		local_env = env_list(env);
	while (status != 0)
	{
		status = input(local_env);
	}
	//if end, destroy env list,
	//free and destroy everything before process end
	return (status);
}
