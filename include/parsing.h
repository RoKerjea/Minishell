/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:41:23 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/21 19:27:08 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../include/minishell.h"
# include "../include/macro.h"

typedef struct s_tok_link
{
	enum e_type			meta;
	char				**str;//need to be char ** for exec, builtins and expander
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
	t_tok_link		*out_list_first;
	struct s_temp	*next;
}	t_temp;

typedef	struct	s_word
{
	char	*word;
	struct s_word	*next;
}				t_word;

//TOKENIZER.C
t_tok_list	*tokenizerstart(char *input);
void	sep_token(char *str, t_tok_list *list);
int	strparser(t_tok_list *list, char *str);
int	metaparser(t_tok_list *list, char *str);
int	metachar_parser(char *str);
int	meta_and_arg_size(char *str);
enum e_type	meta_type(char *str);

//PARSER
t_parsed	*list_parser(t_temp *temp);
t_parsed_cmd	*make_parsed_link(t_temp *temp);
int	get_type(char **cmd_args);
int	is_builtins(char *cmd);
char	**get_args(t_tok_link *token);
int	token_count(t_tok_link *token);

t_temp	*mktemplist(void);
t_temp	*token_sorter(t_tok_list	*list);
void	add_token_arg(t_temp *temp, t_tok_link *link);
int		add_token_in(t_temp *temp, t_tok_link *link);
int		add_token_out(t_temp *temp, t_tok_link *link);

//TOKEN_STRUCT.C
t_tok_list	*make_list();
t_tok_link	*make_add_link(t_tok_list *list);
void		destroy_token(t_tok_link *link);
void		destroy_token_list(t_tok_list *list);

//EXPANDER.C
void	token_expander(t_tok_list *list, t_env *local_env);
char	*expander(char *str, t_env *local_env);
char	*expand_res(char *str, int i, t_env *local_env, char *res);
char	*get_var_content(char *str, t_env *local_env);
char	*extract_name(char *str);
int	wordlen(char *str);
struct	s_word	*make_add_wordlink(char *str, int len, struct	s_word *prevword);
struct	s_word	*make_word_link(char *str, int len);
char	*fuse_and_clean(struct	s_word *wordlink, t_env *local_env);
char	*prototype(char *str, t_env *local_env);

//BOOL_STR.C
int	ft_isspace(char c);
int	is_meta(char c);
int syntax_checker(t_tok_list *list);

//TESTS.C
void	print_temp_list(t_temp *temp);
void	print_temp_link(t_temp *temp);
void	print_token_list(t_tok_link *token);
void	print_parsed_list(t_parsed_cmd *final_link);
void	print_token(t_tok_list *list);

#endif