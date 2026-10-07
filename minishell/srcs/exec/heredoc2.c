/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 04:55:50 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/20 19:49:57 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	is_eof_line(char *line, char *eof)
{
	size_t	eof_len;

	eof_len = ft_strlen(eof);
	return (ft_strncmp(line, eof, eof_len) == 0 && line[eof_len] == '\0');
}

void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	write_expanded_line(int fd, char *line, t_shell *shell)
{
	char	*expanded;

	expanded = expand_string(line, shell->env, shell->exit_code);
	write_line(fd, expanded);
	free(expanded);
}

void	heredoc_warning(char *eof)
{
	ft_putstr_fd(
		"minishell: warning: here-document delimited by end-of-file "
		"(wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// reads one heredoc line: readline if interactive, else gnl (strip newline)
char	*read_heredoc_line(t_shell *shell)
{
	if (shell->interactive)
		return (readline("> "));
	return (readline(""));
}
