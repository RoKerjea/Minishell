/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:47:11 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/26 13:46:37 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//rajouter une ft par builtin pour verifier input format et printerror
//parse what builtin should be launched, then launch it and return exit status of builtin
void	builtin_parser(char *input, t_env *local_env)
{
	if (ft_strncmp(input, "exit", 4) == 0)
		exit (0);//exit value should be unsigned int specified after string "exit" (0 -> 255)
	if (ft_strncmp(input, "env", 3) == 0)
		printenv(local_env);
	if (ft_strncmp(input, "pwd", 3) == 0)
		printpath();
	if (ft_strncmp(input, "cd", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
		change_dir(input, local_env);
	if (ft_strncmp(input, "export ", 7) == 0 && (input[7] != ' ' || input[7] != '\0'))
		update_variable(input + 7, local_env);
	if (ft_strncmp(input, "unset ", 6) == 0 && (input[6] != ' ' || input[6] != '\0'))
		remove_variable(input + 6, local_env);
}

//start of input loop, should add to history, tokenize->parse->expand->send to exec
int	input(t_env *local_env)
{
	char	*input;
	t_tok_list	*list;

	while (1)
	{
		input = readline ("cmd>");
		printf ("//input== \"%s\"\n", input);//to del
		builtin_parser(input, local_env);//ca il faudra le mettre ailleur, mais il marchera pareil
		list = tokenizerstart(input);
		print_token(list);
	}
	return (0);
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
