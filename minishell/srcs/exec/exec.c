/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:01:01 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/15 16:45:25 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	count_cmds(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

// abstraction
static void	exec_child(t_shell *shell, t_cmd *cmd)
{
	int	hd_fd;

	close_unneeded_heredoc_fds(cmd);
	hd_fd = get_last_heredoc_fd(cmd);
	if (hd_fd != -1)
	{
		if (dup2(hd_fd, STDIN_FILENO) == -1)
			exit_child("dup2");
		close(hd_fd);
	}
	if (setup_redirections(cmd))
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_shell(shell);
		exit(1);
	}
	if (!cmd->argv)
		exit_clean(shell, 0);
	if (is_builtin(cmd))
	{
		hd_fd = exec_builtin(shell, cmd);
		exit_clean(shell, hd_fd);
	}
	exec_external(shell, cmd);
}

// set up exec / child signals = default
// control wait + restore prompt signals
static void	exec_single(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (can_run_in_parent(cmd))
		return (run_parent_builtin(shell, cmd));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
		exec_child(shell, cmd);
	waitpid(pid, &status, 0);
	set_exit_status_from_wait(shell, status);
}

// reset next_heredoc_fd once per cmd line
// if prepare_heredocs fails, clean up hd fds & give back prompt
// parent closes its own copies after exec
void	exec_cmds(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return ;
	setup_wait_signals();
	expand_cmds(shell, cmd);
	shell->next_heredoc_fd = SAFE_FD;
	if (prepare_heredocs(shell, cmd))
	{
		cleanup_heredoc_fds(cmd);
		setup_prompt_signals();
		return ;
	}
	if (!cmd->next)
		exec_single(shell, cmd);
	else
		exec_pipeline(shell, cmd, count_cmds(cmd));
	cleanup_heredoc_fds(cmd);
	setup_prompt_signals();
}
