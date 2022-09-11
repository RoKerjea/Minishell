/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:43:34 by nvasilev          #+#    #+#             */
/*   Updated: 2022/09/11 20:48:22 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"

int	str_table_counter(char **str_table);
int	final_exit(t_parsed_cmd *cmd_struct, t_env *local_env);
int	env(char **cmd, t_env *local_env);
int	echo(char **cmd, t_env *local_env);
int	pwd(char **cmd, t_env *local_env);
int	cd(char **cmd, t_env *local_env);
int	env_export(char **cmd, t_env *local_env);
int	env_unset(char **cmd, t_env *local_env);

#endif
