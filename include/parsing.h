/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:41:23 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 17:53:28 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../include/minishell.h"

/* typedef struct s_tok_link
{
	int					meta;
	char				*str;
	struct s_tok_link	*next;
	struct s_tok_link	*prev;
}		t_tok_link;

typedef struct s_tok_list
{
	unsigned int		len;
	struct s_tok_link	*first;
	struct s_tok_link	*last;
}		t_tok_list; */

//TOKENIZER.C
//t_tok_list	*tokenizerstart(char *input);
void	print_token(t_tok_list *list);
t_tok_list *make_list();
t_tok_link *make_add_link(t_tok_list *list);
void	sep_token(char *str, t_tok_list *list);

int	strparser(t_tok_list *list, char *str);
int	metaparser(t_tok_list *list, char *str);
int	find_end_quote(char *str, char c);
int	metachar_parser(char *str);
int	meta_and_arg_size(char *str);

int	meta_type(char *str);


//BOOL_STR.C
int	ft_isspace(char c);
int	is_meta(char c);

#endif