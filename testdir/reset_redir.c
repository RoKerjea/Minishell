/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:49:29 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/11 10:55:51 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	main(void)
{
	int bak, new;
	
	// fflush(stdout);
	bak = dup(1);
	new = open("./outtest", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(new, 1);
	close(new);

	write (1, "what?\n", 7);
	//printf ("ceci est un test\n");

	// fflush(stdout);
	dup2(bak, 1);
	close(bak);
	write (1, "what2?\n", 7);
	return (0);
}