/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:41:23 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/13 14:32:42 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../include/minishell.h"
# include "../include/macro.h"

typedef struct s_tok_link
{
	enum e_type			meta;
	char				*str;
	struct s_tok_link	*next;
	struct s_tok_link	*prev;
}		t_tok_link;

typedef struct s_tok_list
{
	unsigned int		len;
	struct s_tok_link	*first;
	struct s_tok_link	*last;
}		t_tok_list;

typedef struct s_temp
{
	int				type;
	t_tok_link		*cmd_list_first;
	t_tok_link		*cmd_list_last;
	t_tok_link		*in_list_first;
	//t_tok_link		*in_list_last;
	t_tok_link		*out_list_first;
	//t_tok_link		*out_list_last;
	struct s_temp	*next;
}	t_temp;

//TOKENIZER.C
t_tok_list	*tokenizerstart(char *input);
void	print_token(t_tok_list *list);
t_tok_list *make_list();
t_tok_link *make_add_link(t_tok_list *list);
void	sep_token(char *str, t_tok_list *list);

int	strparser(t_tok_list *list, char *str);
int	metaparser(t_tok_list *list, char *str);
int	find_end_quote(char *str, char c);
int	metachar_parser(char *str);
int	meta_and_arg_size(char *str);

enum e_type	meta_type(char *str);


t_temp	*mktemplist(void);
t_temp	*token_sorter(t_tok_list	*list);
void	add_token_arg(t_temp *temp, t_tok_link *link);
int		add_token_in(t_temp *temp, t_tok_link *link);
int		add_token_out(t_temp *temp, t_tok_link *link);

//BOOL_STR.C
int	ft_isspace(char c);
int	is_meta(char c);


//TESTS.C
void	print_temp_list(t_temp *temp);
void	print_temp_link(t_temp *temp);
void	print_token_list(t_tok_link *token);

#endif