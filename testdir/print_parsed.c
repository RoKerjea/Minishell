
#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

void	print_char_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("arg n%d = (%s)\n", i, tab[i]);
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
		printf("CMD %d is of type %d\n", i, final_link->exec_type);
		
		if (final_link->cmd_args)
		{
			printf("cmd args are:\n");
			print_char_tab(final_link->cmd_args);
		}
		if (final_link->redir_in)
		{
			printf("redir in target:");
			printf("%s\n", final_link->redir_in);
		}
		if (final_link->heredoc)
		{
			printf("heredoc delimiteur/target:");
			printf("%s\n", final_link->heredoc);
		}
		if (final_link->redir_out)
		{
			printf("redir out target:");
			printf("%s\n", final_link->redir_out);
		}
		if (final_link->redir_append)
		{
			printf("redir append target:");
			printf("%s\n", final_link->redir_append);
		}
		final_link = final_link->next;
		i++;
	}
}

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
	print_token_list(temp->redir_in);
	printf("out redirections tokens : \n");
	print_token_list(temp->redir_out);
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