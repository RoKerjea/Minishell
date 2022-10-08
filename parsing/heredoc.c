/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:16:11 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/08 15:31:20 by rokerjea         ###   ########.fr       */
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
	while (str[x] <= 'z' && access(str, F_OK) == 0)
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
	if (!res)
		return (0);
	while (access(res, F_OK) == 0)
	{
		temp = ft_strjoin(res, "a");
		free (res);
		if (!temp)
		{
			free (rand);
			return (0);
		}
		res = find_free_name(temp);
	}
	free (rand);
	return (res);
}

//all parameter needed at end of heredoc to go back to non interactive mode
//are changed here
void	heredoc_closing_setup(int filefd, int old_fd, t_tok_link *link)
{
	close (filefd);
	signal(SIGINT, SIG_IGN);
	dup2(old_fd, STDIN_FILENO);
	close(old_fd);
	free(link->str[0]);
}

char	*heredoc_expand(char *input, t_env *local_env)
{
	char	*expanded;

	expanded = str_expander(input, local_env, 0);
	if (expanded != input)
		free (input);
	input = expanded;
	return (input);
}

void	heredoc_input(t_tok_link *link, t_env *local_env, int filefd)
{
	char	*input;

	input = readline ("> ");
	while (input && strcmp(input, link->str[0]) != 0 && errno != EINTR)
	{
		if (link->meta == HEREDOC && ft_strchr(input, '$'))
			input = heredoc_expand (input, local_env);
		write(filefd, input, strlen(input));
		free (input);
		input = readline ("> ");
		if (!input && errno != EINTR && errno != EBADF)
			write(STDERR_FILENO, "\n", 1);
		if (errno == EINTR || errno == EBADF)
		{
			free (input);
			input = NULL;
			local_env->lst_exit = 128 + SIGINT;
		}
		write(filefd, "\n", 1);
	}
}

//filefd == 0 if filepath == 0, both protection at once
char	*heredoc(t_tok_link *link, t_env *local_env)
{
	int		filefd;
	char	*filepath;
	int		old_fd;

	old_fd = dup(STDIN_FILENO);
	filepath = findnewname(link->str[0]);
	filefd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd == -1)
	{
		free (filepath);
		return (0);
	}
	signal(SIGINT, sigint_hd_handler);
	heredoc_input(link, local_env, filefd);
	heredoc_closing_setup(filefd, old_fd, link);
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
