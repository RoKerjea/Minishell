/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:16:11 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/02 19:08:29 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"
#include "../include/common.h"
#include "../include/utils.h"
#include <signal.h>

char	*find_free_name(char *str)
{
	int	x;

	x = ft_strlen(str);
	x--;
	str[x] = 'a';
	while(str[x] <= 'z' && access(str, F_OK) == 0)
	{
		str[x]++;
	}
	return (str);
}

char	*findnewname(char *name)
{
	char	*res;
	char	*temp;
	char	*rand;

	rand = malloc(2);
	rand[1] = '\n';
	res = ft_strjoin("/tmp/", name);
	//protect
	while (access(res, F_OK) == 0)
	{
		temp = ft_strjoin(res, "a");
		//protect
		free (res);
		res = find_free_name(temp);
	}
	free (rand);
	//printf ("name = %s\n", res);
	return (res);
}

//need expand step, which need env
char	*heredoc(t_tok_link *link, t_env *local_env)
{
	int		filefd;
	char	*filepath;
	char	*expanded;
	char	*input;
	int		old_fd;

	old_fd = dup(STDIN_FILENO);
	filepath = findnewname(link->str[0]);
	filefd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//protect
	signal(SIGINT, sigint_hd_handler);
	input = readline ("> ");
	while (input && strcmp(input, link->str[0]) != 0 && errno != EINTR)
	{
		if (link->meta == HEREDOC && ft_strchr(input, '$'))
		{
			expanded = str_expander(input, local_env, 0);
			//protect
			free (input);
			input = expanded;
		}
		write(filefd, input, strlen(input));
		free (input);
		input = readline ("> ");
		if (errno == EINTR || EBADF)//EBADF cause probleme et interrompt heredoc a la deuxieme ligne dans tt les cas!!
		{
			free (input);
			input = NULL;
			local_env->lst_exit = 128 + SIGINT;
		}
		write(filefd, "\n", 1);
	}
	close (filefd);
	signal(SIGINT, SIG_IGN);
	dup2(old_fd, STDIN_FILENO);
	close(old_fd);
	return (filepath);
}
/*
int	main(int ac, char** av)
{
	int		filefd;
	char	*end_of_file;
	char	*filepath;
	char	*input;
	//quote flag?? for expander of line

	if (ac != 2)
	{
		printf("error\n");
		exit (0);
	}
	end_of_file = av[1];
	//filepath = av[1];
	filepath = findnewname(av[1]);
	filefd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input = readline ("> ");
	while (strcmp(input, end_of_file) != 0)
	{
		write(filefd, input, strlen(input));
		input = readline ("> ");
		if (strcmp(input, end_of_file) != 0)
			write(filefd, "\n", 1);
	}
	open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	unlink (filepath);
	close (filefd);
	return (0); //should return filepath in the end
} */

//close in parent AND child process?, but unlink in parent before fork?
