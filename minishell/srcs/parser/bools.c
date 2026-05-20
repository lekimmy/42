/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 04:38:59 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/21 01:02:56 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_token *t)
{
	return (t->type == OPERATOR && t->operator == PIPE);
}

int	is_redir(t_token *t)
{
	return (t->type == OPERATOR && t->operator && t->operator != PIPE);
}

int	is_word(t_token *t)
{
	return (t->type == WORD);
}

t_cmd	*new_command(t_token *t)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(word *));
	if (!cmd->argv)
		return (NULL);
	cmd->argv[0] = NULL;
	while (t && t->operator != PIPE)
	{
		if (is_word(t))
			add_arg(cmd, t->segments);
	}
	return (cmd);
}

void	add_command(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;
	
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}