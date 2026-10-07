/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/22 15:45:29 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	close_all_pipes(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->n - 1)
	{
		close(p->pipes[i][0]);
		close(p->pipes[i][1]);
		i++;
	}
}

void	setup_pipe_fds(t_pipe *p, t_cmd *cmd)
{
	int	hd_fd;

	hd_fd = get_last_heredoc_fd(cmd);
	if (p->i > 0 && dup2(p->pipes[p->i - 1][0], STDIN_FILENO) == -1)
		exit_child("dup2");
	if (p->i < p->n - 1 && dup2(p->pipes[p->i][1], STDOUT_FILENO) == -1)
		exit_child("dup2");
	close_all_pipes(p);
	if (hd_fd != -1 && dup2(hd_fd, STDIN_FILENO) == -1)
		exit_child("dup2");
	if (hd_fd != -1)
		close(hd_fd);
}

// close all heredoc fds belonging to other cmds in the pipeline
void	close_other_cmds_heredoc_fds(t_cmd *all_cmds, t_cmd *my_cmd)
{
	t_heredoc	*hd;
	t_cmd		*cmd;
	int			my_fd;

	my_fd = get_last_heredoc_fd(my_cmd);
	cmd = all_cmds;
	while (cmd)
	{
		hd = cmd->heredocs;
		while (hd)
		{
			if (hd->fd != -1 && hd->fd != my_fd)
			{
				close(hd->fd);
				hd->fd = -1;
			}
			hd = hd->next;
		}
		cmd = cmd->next;
	}
}
