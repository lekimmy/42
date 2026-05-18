/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/19 01:34:23 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell()
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->exit_code = 0;
	return (shell);
}

// !line == ctrl+D = stil reachable valgrind
// return 1 in case of lexing / parsing error
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;
	t_token	*token;

	(void)argc;
	(void)argv;
	(void)envp;
	shell = init_shell();
	if (!shell)
		return (1);
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
		token = NULL;
		if (!tokenize(&token, line))
		{
			shell->exit_code = 2;
			free(line);
			free_all(&token);
			continue;
		}
		free(line);
	}
	return (shell->exit_code);
}
