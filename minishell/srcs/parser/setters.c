/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:52:23 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/28 22:52:32 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_infile(t_token *current, t_cmd *cmd)
{
	cmd->infile = current->next->word;
}

void	set_outfile(t_token *current, t_cmd *cmd)
{
	cmd->outfile = current->next->word;
}

void	set_append(t_token *current, t_cmd *cmd)
{
	cmd->outfile = current->next->word;
	cmd->append = 1;
}

void	set_heredoc_eof(t_token *current, t_cmd *cmd)
{
	cmd->heredoc_eof = current->next->word;
	if (current->next->word->segments->quote_context == NONE)
		cmd->heredoc_expand = 1;
}
