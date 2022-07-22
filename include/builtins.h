/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:19:13 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/22 12:48:30 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../include/minishell.h"

int	final_exit(char **cmd, t_env *local_env);
int	env(char **cmd, t_env *local_env);
int	echo(char **cmd, t_env *local_env);
int	pwd(char **cmd, t_env *local_env);
int	cd(char **cmd, t_env *local_env);
int	env_export(char **cmd, t_env *local_env);
int	env_unset(char **cmd, t_env *local_env);

int (*built[7]) (char **, t_env *);

#endif