/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:39:30 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/09 19:17:00 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// exec builtin and get return value
// use that value as child's exit status
// terminate child immediatly after builtin exec
// propagate builtin's return code to parent via waitpid
// mimic behavior of external cmd that terminates after exec
static void	run_child(t_shell *shell, t_cmd *all_cmds, t_cmd *cmd, t_pipe *p)
{
	int	code;

	setup_pipe_fds(p, cmd);
	close_other_cmds_heredoc_fds(all_cmds, cmd);
	close_unneeded_heredoc_fds(cmd);
	if (setup_redirections(cmd))
	{
		free(p->pipes);
		exit_clean(shell, 1);
	}
	free(p->pipes);
	if (!cmd->argv)
		exit_clean(shell, 0);
	if (is_builtin(cmd))
	{
		code = exec_builtin(shell, cmd);
		exit_clean(shell, code);
	}
	exec_external(shell, cmd);
}

// each command = child
static void	fork_cmds(t_shell *shell, t_cmd *cmd, t_pipe *p)
{
	t_cmd	*all_cmds;
	pid_t	pid;

	all_cmds = cmd;
	p->i = 0;
	all_cmds = cmd;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			exit_child("fork");
		if (pid == 0)
			run_child(shell, all_cmds, cmd, p);
		shell->pids[p->i] = pid;
		cmd = cmd->next;
		p->i++;
	}
}

// WIFEXITED: return True if process returning status exited via exit()
// WEXITSTATUS: return process return code from status
// WIFSIGNALED: return True if process returning status was terminated
//		by a signal
// WTERMSIG: return signal that terminated the process that provided
//		the status value
// wait all processes, return exit code at any termination
static void	wait_all(t_shell *shell, int n)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < n)
		waitpid(shell->pids[i++], &status, 0);
	set_exit_status_from_wait(shell, status);
}

static int	create_pipes(t_pipe *p, int n)
{
	int	i;

	p->pipes = malloc(sizeof(int [2]) * (n - 1));
	if (!p->pipes)
		return (0);
	p->n = n;
	i = 0;
	while (i < n - 1)
	{
		if (pipe(p->pipes[i++]) == -1)
		{
			free(p->pipes);
			return (perror("pipe"), 0);
		}
	}
	return (1);
}

// Parent ignores SIGINT + SIGQUIT > children treats and dies
void	exec_pipeline(t_shell *shell, t_cmd *cmd, int n)
{
	t_pipe	p;

	if (!create_pipes(&p, n))
		return ;
	shell->pids = malloc(sizeof(pid_t) * n);
	if (!shell->pids)
		return (free(p.pipes));
	shell->in_pipeline = 1;
	fork_cmds(shell, cmd, &p);
	shell->in_pipeline = 0;
	close_all_pipes(&p);
	free(p.pipes);
	wait_all(shell, n);
	free(shell->pids);
	shell->pids = NULL;
}
