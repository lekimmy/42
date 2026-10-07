/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:38:02 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/15 16:45:03 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup2_error(int fd)
{
	close(fd);
	perror("dup2");
}

static void	fd_error(char *filename)//, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
}

static int	apply_io_redir(char *filename, t_redir_type type)
{
	int	fd;

	if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == REDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		fd_error(filename);
		return (1);
	}
	if (type == REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (dup2_error(fd), 1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (dup2_error(fd), 1);
	}
	close(fd);
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*curr;
	char	*filename;

	curr = cmd->redirs;
	while (curr)
	{
		filename = word_to_str(curr->file);
		if (!filename)
			return (1);
		if (apply_io_redir(filename, curr->type))
		{
			free(filename);
			return (1);
		}
		free(filename);
		curr = curr->next;
	}
	return (0);
}
