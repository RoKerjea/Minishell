/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/08/30 19:02:35 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"
#include "../include/macro.h"

// CONTENT OF FILE: what's needed to make list of tokens from input
// INPUT: the full line from readline
// OUTPUT: liste chainee de token contenant seulement les '|', str pour cmd,
// et redirections avec leurs cibles

//zsh: parse error near `>'

//start of tokenizer, create list of token, launch token separator,
//syntax check result of this step (if redirection have their arguments)
t_tok_list	*tokenizerstart(char *input)
{
	t_tok_list	*token_list;

	token_list = make_list();
	if (token_list == NULL)
		return (NULL);
	//printf("len of input == %lu\n", strlen(input)); //TEST to delete
	sep_token(input, token_list);//if == ERROR then destroy and return NULL?
	if (token_list->last->meta == FAIL || token_list->len == 0 || syntax_checker(token_list) == NO)
	{
		destroy_token_list(token_list);
		return (NULL);
	}	
	if (syntax_checker(token_list) == NO)//fuse with malloc protection result so destroy isn't repeated??
	{
		destroy_token_list(token_list);
		return (NULL);
	}
	return (token_list);
}

// str_tokenizer et meta_tokenizer cree le maillon, et malloc la bonne taille pour la str
void	sep_token(char *str, t_tok_list *list)
{
	int	i;

	i = 0;
	//printf("//input at start of tokenizer== \"%s\"\n", str);//TEST to delete
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]) == YES && str[i] != '\0')
			i++;
		if (is_meta(str[i]) == NO && str[i] != '\0')
		{
			i += str_tokenizer(list, str + i);
		}
		else if (is_meta(str[i]) == YES && str[i] != '\0')
		{
			i += meta_tokenizer(list, str + i);
		}
		if (list->last->meta == FAIL || list->len == 0)
			return ;
	}
}

int	token_var(t_tok_link *link, char *str, int i)
{
	link->str = malloc(sizeof(char *) * 2);//char **because after split need char** as arg of execve
	if (link->str == NULL)
		return (0);
	link->str[0] = ft_strndup(str, i);
	link->str[1] = 0;
	link->meta = meta_type(link->str[0]);
	//link->str[0] = ft_strtrim_replace(link->str[0], "> <");
	//does it work for every cases? possibly yes
	return (1);
}

// get str until EOL or metachar, presumably part of same cmd for exec
int	str_tokenizer(t_tok_list *list, char *str)
{
	int			i;
	t_tok_link	*link;

	i = 0;
	link = make_add_link(list);//to protect also
	if (link == NULL)
	{
		list->len = 0;//what if this is the first link?
		return (0);
	}
	while (is_meta(str[i]) == NO && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_end_quote(str + i, str[i]);
		else
			i++;
	}
	printf("str in strparse == \"%s\", strlen = %d\n", str, i); // TEST to delete
	if (token_var(link, str, i) == 0)
		return (0);
/* 	link->str = malloc(sizeof(char *) * 2);//char **because after split need char** as arg of execve
	link->str[0] = ft_strndup(str, i);
	link->str[1] = 0;
	printf("str made == \"%s\"\n", link->str[0]); // TEST to delete
	link->meta = CMD; */
	link->str[0] = ft_strtrim_replace(link->str[0], " ");//protect too, maybe only thing needed to protect if inside it, it can manage a char* NULL and return NULL immediatly
	return (i);
}

// get str starting from metachar->create a token with metachar and redirection target, if any,
int	meta_tokenizer(t_tok_list *list, char *str)
{
	int			i;
	t_tok_link	*link;

	i = 0;
	link = make_add_link(list);
	if (link == NULL)
	{
		list->len = 0;
		return (0);
	}
	i += metachar_parser(str);
	printf("str in metaparse == \"%s\", strlen = %d\n", str, i); // TEST to delete
	if (token_var(link, str, i) == 0)
		return (0);
/* 	link->str = malloc(sizeof(char *) * 2);
	link->str[0] = ft_strndup(str, i);
	link->str[1] = 0;
	//protect
	link->meta = meta_type(link->str[0]); */
	if (link->meta == PIPE)
		return (i);
	if (link->meta == IN || link->meta == OUT)//what if strtrim_replce(str, "> <")??? it should get us rid of everything at once!!
		link->str[0] = redir_trimmer(link->str[0], 1);
	if (link->meta == APPEND || link->meta == HEREDOC)
		link->str[0] = redir_trimmer(link->str[0], 2);
	link->str[0] = ft_strtrim_replace(link->str[0], " ");
	return (i);
}

char	*ft_strtrim_replace(char *str, char *totrim)//if str == NULL, return NULL, wich protect without doubling from previous function?? not sure
{
	char	*temp;

	if (str == NULL)
		return (str);
	temp = ft_strtrim(str, totrim);
	free (str);
	str = temp;
	return (str);
}
