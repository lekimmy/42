/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 04:55:50 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/23 20:31:12 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// only last fd survives on multi <<
int	get_last_heredoc_fd(t_cmd *cmd)
{
	t_heredoc	*hd;
	int			fd;

	fd = -1;
	hd = cmd->heredocs;
	while (hd)
	{
		fd = hd->fd;
		hd = hd->next;
	}
	return (fd);
}

// scope = single cmd (every child) before exec
// last heredoc fd overrides all previous
// clean up all except last on multi <<
void	close_unneeded_heredoc_fds(t_cmd *cmd)
{
	t_heredoc	*hd;
	int			last_fd;

	hd = cmd->heredocs;
	last_fd = get_last_heredoc_fd(cmd);
	while (hd)
	{
		if (hd->fd != -1 && hd->fd != last_fd)
		{
			close(hd->fd);
			hd->fd = -1;
		}
		hd = hd->next;
	}
}

// close any heredoc fd already dup2'd to a safe slot before this child existed
void	close_inherited_heredoc_fds(t_shell *shell)
{
	int	fd;

	fd = SAFE_FD;
	while (fd < shell->next_heredoc_fd)
	{
		close(fd);
		fd++;
	}
}

// scope = all cmds (parent) on failure
// clean up all fds after ctrl+c / error
void	cleanup_heredoc_fds(t_cmd *cmd)
{
	t_heredoc	*hd;

	while (cmd)
	{
		hd = cmd->heredocs;
		while (hd)
		{
			if (hd->fd != -1)
			{
				close(hd->fd);
				hd->fd = -1;
			}
			hd = hd->next;
		}
		cmd = cmd->next;
	}
}

// non-interactive: read heredoc in the parent (no fork) to keep gnl buffer
// consistent; lines come from the same STDIN stream as the command input
int	collect_heredoc_nofork(t_shell *shell, t_heredoc *hd)
{
	int		pipefd[2];
	char	*eof;

	if (pipe(pipefd) == -1)
		return (1);
	eof = word_to_str(hd->eof);
	if (!eof)
		return (close(pipefd[0]), close(pipefd[1]), 1);
	read_heredoc_lines(pipefd[1], hd->expand, shell, eof);
	free(eof);
	close(pipefd[1]);
	hd->fd = pipefd[0];
	if (dup2(hd->fd, shell->next_heredoc_fd) == -1)
		return (close(pipefd[0]), 1);
	close(hd->fd);
	hd->fd = shell->next_heredoc_fd++;
	return (0);
}
