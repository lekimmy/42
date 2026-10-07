/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietri <mpietri@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:59:26 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/23 21:59:29 by mpietri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	can_run_in_parent(t_cmd *cmd)
{
	char	*name;

	if (!cmd->argv)
		return (0);
	name = word_to_str(cmd->argv);
	if (!name)
		return (0);
	if (!*name)
		return (free(name), 0);
	free(name);
	return (is_builtin(cmd));
}

void	run_parent_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->infile && !cmd->outfile && !cmd->heredocs)
	{
		shell->exit_code = exec_builtin(shell, cmd);
		return ;
	}
	if (save_stdio(&shell->io))
		return ;
	if (setup_redirections(cmd))
	{
		restore_stdio(&shell->io);
		shell->exit_code = 1;
		return ;
	}
	shell->exit_code = exec_builtin(shell, cmd);
	restore_stdio(&shell->io);
}
