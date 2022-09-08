/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:43:34 by nvasilev          #+#    #+#             */
/*   Updated: 2022/07/23 00:46:19 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"

int	final_exit(char **cmd, t_env *local_env);
int	env(char **cmd, t_env *local_env);
int	echo(char **cmd, t_env *local_env);
int	pwd(char **cmd, t_env *local_env);
int	cd(char **cmd, t_env *local_env);
int	env_export(char **cmd, t_env *local_env);
int	env_unset(char **cmd, t_env *local_env);

#endif
