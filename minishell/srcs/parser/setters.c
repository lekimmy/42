/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:52:23 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/09 16:02:24 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir_back(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

static t_redir	*create_redir(t_token *current, t_redir_type type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = current->next->word;
	new_redir->next = NULL;
	return (new_redir);
}

void	set_infile(t_token *current, t_cmd *cmd)
{
	cmd->infile = current->next->word;
	add_redir_back(&cmd->redirs, create_redir(current, REDIR_IN));
}

void	set_outfile(t_token *current, t_cmd *cmd)
{
	cmd->outfile = current->next->word;
	cmd->append = 0;
	add_redir_back(&cmd->redirs, create_redir(current, REDIR_OUT));
}

void	set_append(t_token *current, t_cmd *cmd)
{
	cmd->outfile = current->next->word;
	cmd->append = 1;
	add_redir_back(&cmd->redirs, create_redir(current, REDIR_APPEND));
}
