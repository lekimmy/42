/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/12 19:43:41 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !line == ctrl+D = stil reachable valgrind
int main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char *line;
	t_token	*token;
	
	token = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			free_all(&token);
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokenize(&token, line);
		if (!token)
			return (free(line), 1);
		free(line);
	}
	return (0);
}
