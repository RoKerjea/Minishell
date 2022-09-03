
#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

//TEST FT only needed to check step result, to delete!
void	print_token(t_tok_list *list)
{
	t_tok_link	*link;
	int	i;
	int j;

	i = 1;
	j = 0;
	link = list->first;
	printf("Token list len = %d\n", list->len);
	printf("Token list after separator in one char* by token :\n");
	while (link != NULL)
	{
		j = 0;
		printf("Token n%d is of type %d\n", i, link->meta);
		while (link->str[j])
		{
			printf ("str n%d == (%s)\n", j, link->str[j]);
			j++;
		}
		link = link->next;
		i++;
	}
}