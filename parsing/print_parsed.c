
#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

/* typedef struct s_parsed_link
{
	int						*type;//defini en MACRO avec un int pour CMD, BUILTIN
	char					**cmd_args;//pour les arguments et options(args[0] SHOULD be the cmd name, by convention)
	int						*fdins;//list de fdin pour la cmd, avec seulement la derniere a utiliser(2, 3, 4 ou rien) but need to open and close all others...
	char					**fdins_args;//cible des redirections correspondantes a leurs fdins...
	int						*fdouts;// (2, 5, 6 ou rien)
	char					**fdouts_args;//cibles si il y a
	struct s_parsed_link	*next;//if NULL, first cmd, if not NULL, pipe fdin exist but maybe not used for this cmd
	struct s_parsed_link	*prev;//if NULL, last cmd, if both NULL, only one cmd, so no pipe, and no fork for builtins
}		t_parsed_link; */

//TODO, redo for tests
/* void	print_parsed_list(struct s_parsed_link *final_link)
{
	int i;
	i = 0;
	while (final_link != NULL)
	{
		printf("Maillon %d is of type %d\n", i, final_link->type);
		printf("cmd args are:\n");
		print_char_tab(final_link->cmd_args);
		printf("input redirections are of types:\n");
		print_int_tab(final_link->fdins);
		printf("and their targets are:\n");
		print_char_tab(final_link->fdins_args);
		printf("output redirections are of types:\n");
		print_int_tab(final_link->fdouts);
		printf("and their targets are:\n");
		print_char_tab(final_link->fdouts_args);
		final_link = final_link->next;
		i++;
	}
}

void	print_int_tab(int *tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		printf("redir n%d = %d", i, tab[i]);
		i++;
	}
}

void	print_char_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("arg n%d = %s", i, tab[i]);
		i++;
	}
} */

/* typedef struct s_temp
{
	t_tok_link	*cmd_list_first;
	t_tok_link	*cmd_list_last;
	t_tok_link	*in_list_first;
	t_tok_link	*in_list_last;
	t_tok_link	*out_list_first;
	t_tok_link	*out_list_last;
	t_temp		*next;

}	t_temp; */

void	print_temp_list(t_temp *temp)
{
	int i;

	i = 0;
	while (temp != NULL)
	{
		printf("cmd n %d is composed from the following tokens:\n", i);
		print_temp_link(temp);
		i++;
	}
}

void	print_temp_link(t_temp *temp)
{
	printf("str tokens : \n");
	print_token_list(temp->cmd_list_first);
	printf("in redirections tokens : \n");
	print_token_list(temp->in_list_first);
	printf("out redirections tokens : \n");
	print_token_list(temp->out_list_first);
}

void	print_token_list(t_tok_link *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		printf("token %d, type= %d, arg= %s", i, token->meta, token->str);
		token = token->next;
		i++;
	}
}