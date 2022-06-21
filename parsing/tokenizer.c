/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:43 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/21 20:49:56 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
BUT : fournir une liste chainee cree a partir de inputstr
->parcourir str, creer un maillon pour chaque mot complet, metachar seul et str entre quotes
(avec marqueur de debut et find d'inputstr specifiques?)
Virer les espaces pas entre quotes,
return liste avec un maillon par str, a reassembler par lexer ensuite en cmdstr et metachar important
redirections et leurs cibles en un seul token?
meme chose pour heredoc start et son EOF?
*/

/*
quotes:
if char[i] == '\'' ou '\"'

i++ until quotes, if same as start, end of quoted str,
else, new cycle with other quoteas start,
repeat until EOF or end of every quotes
if EOF, error
else, full str is between first quote and end of last cycle closed;

no need to remember except the last end quote, and start position is always to keep anyway
can be a recursive cycle of same function who only return last position and add to i
!!PB, $VAR must expand if only between "", could be slightly annoying to find if opened '' when $VAR
but functions for quotes could give beginning and end position too...
lots of parameter for a single string...could keep coordinates of '' "zones" for this string?
*/

/*
could use a program test exec by minishell
cmd "binary arg1arg2 'arg3'arg4"
and it gives number et format of args it received?
*/