/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/22 15:05:45 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"
#include "../include/macro.h"

//need to divide into creation and parsing?
// FILE: what's needed to make list of tokens from input
// INPUT: the full line from readline
// OUTPUT: liste chainee de token contenant seulement les '|', str pour cmd,
// et redirections avec leurs cibles
//zsh: parse error near `>'

//start of tokenizer, create list of token, launch token separator,
//syntax check result of this step (if redirection have their arguments)
t_tok_list *tokenizerstart(char *input)
{
	t_tok_list *token_list;

	token_list = make_list();
	printf("len of input == %lu\n", strlen(input)); //TEST to delete
	sep_token(input, token_list);
	//protect
	if (syntax_checker(token_list) == NO)
	{
		destroy_token_list(token_list);
		return (NULL);
	}
	return (token_list);
}

// strparser et metaparser cree le maillon, et malloc la bonne taille pour la str
void sep_token(char *str, t_tok_list *list)
{
	int i;

	i = 0;
	printf("//input at start of tokenizer== \"%s\"\n", str); // TEST to delete
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]) == YES && str[i] != '\0')
			i++;
		if (is_meta(str[i]) == NO && str[i] != '\0')
		{
			i += strparser(list, str + i);
			//protect
		}
		else if (is_meta(str[i]) == YES && str[i] != '\0')
		{
			i += metaparser(list, str + i);
			//protect
		}
	}
}

// get str until EOL or metachar, presumably part of same cmd for exec
int strparser(t_tok_list *list, char *str)
{
	int i;
	t_tok_link *link;

	i = 0;
	link = make_add_link(list);
	while (is_meta(str[i]) == NO && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i, str[i]);
		else
			i++;
	}
	printf("str in strparse == \"%s\", strlen = %d\n", str, i); // TEST to delete
	link->str = malloc(sizeof(char *) * 2);
	link->str[0] = ft_strndup(str, i);
	link->str[1] = 0;
	//protect
	printf("str made == \"%s\"\n", link->str[0]); // TEST to delete
	link->meta = CMD;
	link->str[0] = ft_strtrim_replace(link->str[0], " ");
	return (i);
}

// get str starting from metachar->create a token with metachar and redirection target, if any,
int metaparser(t_tok_list *list, char *str)
{
	int i;
	t_tok_link *link;
	char	*temp;

	i = 0;
	link = make_add_link(list);
	i += metachar_parser(str);
	printf("str in metaparse == \"%s\", strlen = %d\n", str, i); // TEST to delete
	link->str = malloc(sizeof(char *) * 2);
	link->str[0] = ft_strndup(str, i);
	link->str[1] = 0;
	//protect
	link->meta = meta_type(link->str[0]);
	if (link->meta == IN || link->meta == OUT)
	{
		temp = link->str[0];
		link->str[0] = ft_strdup(link->str[0] + 1);
		free (temp);
	}
	if (link->meta == APPEND || link->meta == HEREDOC)
	{
		temp = link->str[0];
		link->str[0] = ft_strdup(link->str[0] + 2);
		free (temp);
	}
	link->str[0] = ft_strtrim_replace(link->str[0], " ");
	return (i);
}

char	*ft_strtrim_replace(char *str, char *totrim)
{
	char	*temp;
	
	temp = ft_strtrim(str, " ");
	free (str);
	str = temp;
}

// identify the type of redirection the current token is
enum e_type	meta_type(char *str)
{
	if (strncmp(str, "<<", 2) == 0)
	{
		if (strchr(str, '\'') != 0)
			return (HEREDOC_NOEXPAND);
		return (HEREDOC);
	}
	if (strncmp(str, "<", 1) == 0)
		return (IN);
	if (strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (strncmp(str, ">", 1) == 0)
		return (OUT);
	if (strncmp(str, "|", 1) == 0)
		return (PIPE);
	else
		return (FAIL);
}

// fnd & return the length of meta token, from the metachar,
// to the end of it's arg, if any
int metachar_parser(char *str)
{
	if (strncmp(str, "<<", 2) == 0 || strncmp(str, ">>", 2) == 0)
		return (meta_and_arg_size(str + 2) + 2);
	if (strncmp(str, "<", 1) == 0 || strncmp(str, ">", 1) == 0)
		return (meta_and_arg_size(str + 1) + 1);
	if (strncmp(str, "|", 1) == 0)
		return (1);
	else
		return (0);
}

// find & return the length of arg of redirection token
int meta_and_arg_size(char *str) // could be fused later with str parser?
{
	int i;

	i = 0;
	while (ft_isspace(str[i]) == YES && str[i] != '\0')
		i++;
	while (is_meta(str[i]) == NO && ft_isspace(str[i]) == NO && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i, str[i]);
		else
			i++;
	}
	return (i);
}
