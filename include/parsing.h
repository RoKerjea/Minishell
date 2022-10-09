/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:41:23 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 17:47:03 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../include/minishell.h"
# include "../include/macro.h"

typedef struct s_tok_link
{
	enum e_type			meta;
	char				**str;
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
	t_tok_link		*redir_in;
	t_tok_link		*redir_out;
	struct s_temp	*next;
}	t_temp;

typedef struct s_word
{
	char			*word;
	struct s_word	*next;
}				t_word;

//TOKENIZER.C
t_tok_list		*tokenizerstart(char *input);
void			sep_token(char *str, t_tok_list *list);
int				str_tokenizer(t_tok_list *list, char *str);
int				meta_tokenizer(t_tok_list *list, char *str);

//FT_STRTRIM_REPLACE_C
char			*ft_strtrim_replace(char *str, char *totrim);

//TOKEN_PARSE.C
char			*redir_trimmer(char	*str, int i);
enum e_type		meta_type(char *str);
int				metachar_parser(char *str);
int				meta_and_arg_size(char *str);

//PARSER
int				check_parsed_cmd(t_parsed *parsed_list);
void			destroy_final_list(t_parsed *parsed_list);

//TOKEN_TO_CMD.C
t_parsed		*list_parser(t_temp *temp);
t_parsed_cmd	*make_parsed_link(t_temp *temp);
char			**empty_tab(void);
char			**get_args(t_tok_link *token);

//TOKEN_TO_CMD_UTILS_C
int				get_type(char **cmd_args);
int				is_builtins(char *cmd);
int				token_count(t_tok_link *token);

//TOKEN ASSIGN
t_temp			*temp_sorter(t_tok_list *list, t_env *local_env);
int				add_token_in(t_temp *temp, t_tok_link *link, t_env *local_env);
int				add_token_out(t_temp *temp, t_tok_link *link);

//TOKEN ASSIGN_UTILS_C
t_temp			*mktemplist(void);
void			add_token_arg(t_temp *temp, t_tok_link *link);
int				is_not_pipe(t_tok_link *link);
void			printerror(char *prob);
int				delete_heredoc_file(t_temp *temp);

//TOKEN_STRUCT.C
t_tok_list		*make_list(void);
t_tok_link		*make_add_link(t_tok_list *list);
void			destroy_token(t_tok_link *link);
void			destroy_token_list(t_tok_list *list);
void			make_last_token(t_tok_list *list);

//EXPANDER.C

char			*str_expander(char *str, t_env *local_env, int expand);
char			*smartass(char *str, int i, t_env *local_env);
char			*get_right_str(char	*str);
void			token_expander(t_tok_list *list, t_env *local_env);
char			*expander(char *str, t_env *local_env);
char			*expand_res(char *str, int i, t_env *local_env, char *res);
char			*get_var_content(char *str, t_env *local_env);
char			*extract_name(char *str);
int				wordlen(char *str);
struct s_word	*make_add_wordlink(char *str, int len, struct s_word *prevword);
struct s_word	*make_word_link(char *str, int len);
char			*fuse_and_clean(struct	s_word *wordlink, t_env *local_env);
char			*prototype(char *str, t_env *local_env);

//FIELD_SPLITTER.C
int				token_splitter(t_tok_list	*list);
char			**char_tab_fuser(char **str1, char **str2);
int				field_counter(char *s, char c);
int				len_field(char *s, char c);
char			**new_char_tab(char **str1, char **str2);

//UNQUOTER.C
int				unquoter_loop(t_tok_list *list);
int				unquote_link(t_tok_link *link);
int				squash(char *str, int start);
char			*unquoter(char *str);

//BOOL_STR.C
int				ft_isspace(char c);
int				is_meta(char c);
int				syntax_checker(t_tok_list *list);

int				str_table_counter(char **str_table);

//HEREDOC_C
char			*heredoc(t_tok_link *link, t_env *local_env);
char			*find_free_name(char *str);
char			*findnewname(char *name);

#endif