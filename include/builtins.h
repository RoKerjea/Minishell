/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:19:13 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/09 16:02:27 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"
# include "minishell.h"

int	str_table_counter(char **str_table);

//EXIT_C
int	final_exit(t_parsed_cmd *cmd_struct, t_env *local_env);

//ENV_C
int	env(char **cmd, t_env *local_env);

int	echo(char **cmd, t_env *local_env);
int	pwd(char **cmd, t_env *local_env);
int	cd(char **cmd, t_env *local_env);
int	env_export(char **cmd, t_env *local_env);
int	env_unset(char **cmd, t_env *local_env);
void	destroy_cmd_link(t_parsed_cmd* link);

//EXIT_PARSER_C
int			is_not_num(char *str);
int			is_char_space(char c);
int			count_spaces(const char *str);
long long	ft_atoll(const char *str);
int			check_overflow(const char *str);

#endif