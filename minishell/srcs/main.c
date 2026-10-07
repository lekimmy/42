/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/22 16:05:32 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = get_env_from_envp(envp);
	shell->interactive = isatty(STDIN_FILENO);
	shell->next_heredoc_fd = SAFE_FD;
	shell->io.stdin_fd = -1;
	shell->io.stdout_fd = -1;
	return (shell);
}

static void	run_line(t_shell *shell, char *line)
{
	t_token	*token;
	t_cmd	*cmd;

	token = NULL;
	if (!tokenize(&token, line) || !validate_syntax(token))
	{
		handle_lex_parse_error(shell, &token);
		return ;
	}
	cmd = NULL;
	if (!parse_argv(&cmd, token))
	{
		free_tokens(&token);
		return ;
	}
	free_token_list(&token);
	if (!cmd)
	{
		free_cmds(&cmd);
		return ;
	}
	shell->cmd = cmd;
	exec_cmds(shell, cmd);
	shell->cmd = NULL;
	free_cmds(&cmd);
}

static void	shell_loop(t_shell *shell)
{
	while (1)
	{
		shell->line = readline("minishell> ");
		if (g_sigint)
		{
			shell->exit_code = 130;
			g_sigint = 0;
		}
		if (!shell->line)
		{
			if (shell->interactive)
				printf("exit\n");
			else
				write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (*shell->line)
			add_history(shell->line);
		run_line(shell, shell->line);
		free(shell->line);
		shell->line = NULL;
	}
}

void	run_non_interactive(t_shell *shell)
{
	shell->line = get_next_line(STDIN_FILENO);
	while (shell->line)
	{
		run_line(shell, shell->line);
		free(shell->line);
		shell->line = get_next_line(STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	setup_prompt_signals();
	if (shell->interactive)
		shell_loop(shell);
	else
		run_non_interactive(shell);
	free_shell(shell);
	return (0);
}
