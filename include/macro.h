/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:16:40 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/09 17:07:54 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

enum e_bool
{
	NO,
	YES
};

enum e_exec
{
	CMD,
	BUILT
};

enum e_redir
{
	PIPE,
	IN,
	HEREDOC,
	OUT,
	APPEND
};

#endif
