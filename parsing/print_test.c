
void	print_parsed_list(struct s_parsed_link)
{
	int i;
	i = 0;
	while (s_parsed_link != NULL)
	{
		printf("Maillon %d is of type %d\n", i, s_parsed_link->type);
		//print char**
		//print redir type and itt's arg
		//same
		s_parsed_link = s_parsed_link->next;
		i++;
	}
}