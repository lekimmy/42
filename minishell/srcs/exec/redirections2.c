/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:03:09 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/22 13:47:52 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// a builtin running in the parent must not lose its real stdin/stdout when
// the command carries redirections, so we keep a copy of both beforehand
int	save_stdio(t_stdio *io)
{
	io->stdin_fd = dup(STDIN_FILENO);
	if (io->stdin_fd == -1)
		return (perror("dup"), 1);
	io->stdout_fd = dup(STDOUT_FILENO);
	if (io->stdout_fd == -1)
	{
		close(io->stdin_fd);
		io->stdin_fd = -1;
		return (perror("dup"), 1);
	}
	return (0);
}

// puts the saved descriptors back in place and closes the copies
void	restore_stdio(t_stdio *io)
{
	if (!io)
		return ;
	if (io->stdin_fd != -1)
	{
		dup2(io->stdin_fd, STDIN_FILENO);
		close(io->stdin_fd);
		io->stdin_fd = -1;
	}
	if (io->stdout_fd != -1)
	{
		dup2(io->stdout_fd, STDOUT_FILENO);
		close(io->stdout_fd);
		io->stdout_fd = -1;
	}
}
