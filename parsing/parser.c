/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:19 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/22 18:31:43 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_parsed_link
{
	int						*type;//defini en MACRO avec un int pour CMD, PIPE, IN, OUT, HEREDOC, APPEND
	char					**cmdstr;//une liste de str* avec str[0] pour la cmd, donc facile a parser pour builtins, path absolu ou relatif etc
										//et avec str[x] pour les arguments et options;
										//(ou la cible pour les redirections, ou le EOF pour le heredoc)
	struct s_parsed_link	*next;
	struct s_parsed_link	*prev;
}		t_parsed_link;

typedef struct s_parsed_input
{
	unsigned int		len;
	struct s_parsed_link	*first;
	struct s_parsed_link	*last;
}		t_parsed_input;

/*
BUT : Fournir une liste chainee avec des inputs fixes et un type pour ce maillon
strcomp to determine type 
input : plein de char *str separe, les espaces ignores si ils sont a l'exterieur de quotes,
les metachars dans leurs str* a part(si pas inside quotes) VAR deja etendues par expander
*/