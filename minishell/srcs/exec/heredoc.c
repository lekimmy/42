/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/08 19:44:16 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// write in dedicated fd
// input ignored if not the last one (dup2 into STDIN)
// or function doesn't write to STDIN
void	read_heredoc_lines(int fd, int expand, t_shell *shell, char *eof)
{
	char	*line;

	while (1)
	{
		line = read_heredoc_line(shell);
		if (g_sigint)
			handle_heredoc_exit(fd, shell, eof);
		if (!line)
		{
			if (!g_sigint)
				heredoc_warning(eof);
			break ;
		}
		if (is_eof_line(line, eof))
		{
			free(line);
			break ;
		}
		if (expand)
			write_expanded_line(fd, line, shell);
		else
			write_line(fd, line);
		free(line);
	}
}

static void	heredoc_child(int pipefd[2], t_shell *shell, t_heredoc *hd)
{
	char	*eof;

	eof = word_to_str(hd->eof);
	if (!eof)
		exit_child("heredoc eof");
	setup_heredoc_signals();
	close(pipefd[0]);
	close_inherited_heredoc_fds(shell);
	read_heredoc_lines(pipefd[1], hd->expand, shell, eof);
	close(pipefd[1]);
	free(eof);
	free_shell(shell);
	exit(0);
}

// helper norm for collect_heredoc
static void	setup_hd_fd(int pipefd[2], t_shell *shell, t_heredoc *hd)
{
	hd->fd = pipefd[0];
	if (dup2(hd->fd, shell->next_heredoc_fd) == -1)
		exit_child("dup2");
}

// read input + build fd
// parent ignores signals
// heredoc signal handling in child
// restore prompt state afterward
static int	collect_heredoc(t_shell *shell, t_heredoc *hd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (!shell->interactive)
		return (collect_heredoc_nofork(shell, hd));
	if (pipe(pipefd) == -1)
		exit_child("pipe");
	setup_wait_signals();
	pid = fork();
	if (pid == -1)
		exit_child("fork");
	if (pid == 0)
		heredoc_child(pipefd, shell, hd);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	restore_prompt_state();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipefd[0]), set_exit_status(shell, status), 1);
	setup_hd_fd(pipefd, shell, hd);
	close(pipefd[0]);
	hd->fd = shell->next_heredoc_fd++;
	return (0);
}

// int safe_heredoc_fd = dup_to_safe_fd(hd->fd);
// if (safe_heredoc_fd == -1)
// 	exit_child("dup_to_safe_fd");
// hd->fd = safe_heredoc_fd;
int	prepare_heredocs(t_shell *shell, t_cmd *cmd)
{
	t_heredoc	*hd;

	while (cmd)
	{
		hd = cmd->heredocs;
		while (hd)
		{
			if (collect_heredoc(shell, hd))
				return (1);
			hd = hd->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
