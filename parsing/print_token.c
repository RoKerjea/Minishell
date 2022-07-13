
#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

//TEST FT only needed to check step result, to delete!
void	print_token(t_tok_list *list)
{
	t_tok_link	*link;
	int	i;

	i = 1;
	link = list->first;
	printf("Token list len = %d\n", list->len);
	printf("Token list after separator in one char* by token :\n");
	while (link != NULL)
	{
		printf("Token n%d is of type %d, str == (%s) \n", i, link->meta, link->str);
		link = link->next;
		i++;
	}
}