/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:34:32 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/08 19:41:16 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_lex_parse_error(t_shell *shell, t_token **token)
{
	shell->exit_code = 2;
	free_tokens(token);
}

void	syntax_error(char *msg, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (token)
	{
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}

// helper norm for collect_heredoc
// shell->exit_code = 128 + WTERMSIG(status); child = 0
void	set_exit_status(t_shell *shell, int status)
{
	shell->exit_code = WEXITSTATUS(status);
	write(1, "\n", 1);
}

void	set_exit_status_from_wait(t_shell *shell, int status)
{
	if (WIFSIGNALED(status))
	{
		shell->exit_code = 128 + WTERMSIG(status);
		write(1, "\n", 1);
	}
	else if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}

void	handle_heredoc_exit(int fd, t_shell *shell, char *eof)
{
	close(fd);
	free(eof);
	free_shell(shell);
	exit(130);
}
