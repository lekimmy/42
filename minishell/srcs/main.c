/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/05 23:37:04 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !line == ctrl+D
int main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char *line;
	t_token	*token;
	
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokenize(&token, line);
		free(line);
	}
	return (0);
}
