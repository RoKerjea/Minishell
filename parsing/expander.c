/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:06:01 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/06 20:25:46 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/macro.h"
#include "../include/parsing.h"

// CONTENT OF FILE: what's needed to expand content of tokenlink->str[0]
// correspondning to env variable
// INPUT: linked list of token
// OUTPUT: same list but with expander step executed on str

//expander function, to be used after tokenizer but before parser
//send input str back but with $VAR replaced by its content in env
void	token_expander(t_tok_list *list, t_env *local_env)
{
	t_tok_link	*token;
	char		*expanded;

	token = list->first;
	while (token != NULL)
	{
		if (ft_strchr(token->str[0], '$') != 0 && token->meta != HEREDOC
			&& token->meta != HEREDOC_NOEXPAND)
		{
			expanded = str_expander(token->str[0], local_env, 1);
			if (!expanded)
			{
				free (token->str[0]);
				return ;
			}			
			if (expanded != token->str[0])
				free (token->str[0]);
			token->str[0] = expanded;
		}
		token = token->next;
	}
}

int	is_to_expand(int quote, int i, char *str)
{
	if (quote == 1 && (str[i + 1] == ' ' || str[i + 1] == '\"'))
		return (NO);
	else if (str[i + 1] == ' ' || str[i + 1] == '\0'
		|| str[i + 1] == '+' || str[i + 1] == '=')
		return (NO);
	return (YES);
}

char	*str_expander(char *str, t_env *local_env, int expand)
{
	int		quote;
	int		i;

	i = 0;
	quote = -1;
	while (str[i])
	{
		if (str[i] == '\"')
			quote *= -1;
		if (str[i] == '\'' && quote == -1 && expand == 1)
			i += find_end_quote(str + i, '\'');
		else if (str[i] == '$')
		{
			if (!is_to_expand(quote, i, str))
				i++;
			else
			{
				str = smartass(str, i, local_env);
				i = 0;
			}
		}
		else
			i++;
	}
	return (str);
}

char	*smartass(char *str, int i, t_env *local_env)
{
	char	*var;
	char	*left_str;
	char	*right_str;
	char	*temp;

	left_str = ft_strndup(str, i);
	right_str = get_right_str (str + i);
	var = get_var_content (str + i, local_env);
	temp = ft_strjoin (left_str, var);
	free (left_str);
	free (var);
	left_str = temp;
	temp = ft_strjoin(left_str, right_str);
	free (left_str);
	free (right_str);
	return (temp);
}

char	*get_right_str(char	*str)
{
	str += wordlen(str);
	return (ft_strdup(str));
}

char	*get_var_content(char *str, t_env *local_env)
{
	char		*res;
	char		*name;
	t_env_link	*link;

	name = extract_name(str);
	if (!strncmp(name, "?", 3))
	{
		free (name);
		return (ft_itoa(local_env->lst_exit));
	}
	link = find_link(name, local_env);
	free (name);
	if (link == NULL)
		return (ft_strdup(""));
	res = ft_strdup(link->variable);
	return (res);
}

char	*extract_name(char *str)
{
	char	*name;
	int		i;

	i = wordlen(str);
	name = ft_strndup(str + 1, i - 1);
	return (name);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (YES);
	return (NO);
}

int	wordlen(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[i]))
		return (i + 1);
	while (str[i] != 36 && str[i] != '\0' && ft_isspace(str[i]) == NO
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '/' && str[i] != '='
		&& str[i - 1] != '?')
		i++;
	return (i);
}
