
#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

void	print_char_tab(char **tab)
{
	int i;

	i = 0;
	printf("gate\n");
	while (tab[i] != NULL && tab[i][0] != '\0')
	{
		printf("arg n%d = %s\n", i, tab[i]);
		i++;
	}
}

//TODO, redo for tests
void	print_parsed_list(t_parsed_cmd *final_link)
{
	int i;
	i = 0;
	while (final_link != NULL)
	{
		printf("Maillon %d is of type %d\n", i, final_link->exec_type);
		
		if (final_link->cmd_args != NULL)
		{
			printf("cmd args are:\n");
			print_char_tab(final_link->cmd_args);
		}
		if (final_link->redir_in != NULL)
		{
			printf("redir in target:");
			printf("%s\n", final_link->redir_in);
		}
		if (final_link->heredoc != NULL)
		{
			printf("heredoc delimiteur/target:");
			printf("%s\n", final_link->heredoc);
		}
		if (final_link->redir_out != NULL)
		{
			printf("redir out target:");
			printf("%s\n", final_link->redir_out);
		}
		if (final_link->redir_append != NULL)
		{
			printf("redir append target:");
			printf("%s\n", final_link->redir_append);
		}
		final_link = final_link->next;
		i++;
	}
}

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
		temp = temp->next;
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
		printf("token %d, type= %d, arg= %s\n", i, token->meta, token->str[0]);
		token = token->next;
		i++;
	}
}