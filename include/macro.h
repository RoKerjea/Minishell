/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:16:40 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/22 15:01:18 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

enum e_bool
{
	NO,
	YES
};

enum e_type
{
	FAIL,
	CMD,
	BUILT,
	PIPE,
	IN,
	HEREDOC,
	HEREDOC_NOEXPAND,
	OUT,
	APPEND
};

#endif
