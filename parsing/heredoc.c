/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:16:11 by rokerjea          #+#    #+#             */
/*   Updated: 2022/09/18 16:39:24 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = malloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}*/

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
	printf ("name = %s\n", res);
	return (res);
}


//need expand step, which need env
char	*heredoc(char *delimiter)
{
	int		filefd;
	char	*filepath;
	char	*input;

	filepath = findnewname(delimiter);
	filefd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input = readline ("> ");
	while (strcmp(input, delimiter) != 0)
	{
		write(filefd, input, strlen(input));
		input = readline ("> ");
		write(filefd, "\n", 1);
	}
	//write(filefd, "\0", 1);
	close (filefd);
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