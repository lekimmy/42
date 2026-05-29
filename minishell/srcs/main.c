/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/29 02:28:48 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = get_env_from_envp(envp);
	shell->exit_code = 0;
	shell->pids = NULL;
	shell->interactive = 0;
	return (shell);
}

// !line == ctrl+D = stil reachable valgrind
// return 1 in case of lexing / parsing error
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;
	t_token	*token;
	// t_cmd	*cmd;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	int i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			free_tokens(&token);
			// free_env(&shell->env);
			// free(shell);
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
			free_tokens(&token);
			// free_env(&shell->env);
			// free(shell);
			continue;
		}
		// cmd = NULL;
		free(line);
	}
	return (shell->exit_code);
}
