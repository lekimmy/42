/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/28 22:53:34 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// realloc forbidden = manual
// get n of existing args
// malloc +1 new arg + NULL terminate
// alloc existing args + strdup new arg
static void	add_arg(t_word **argv, t_word *word)
{
	t_word	*current;

	if (!*argv)
	{
		*argv = word;
		return ;
	}
	current = *argv;
	while (current->next)
		current = current->next;
	current->next = word;
}

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc_eof = NULL;
	cmd->heredoc_expand = 0;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*new_command(t_token *t)
{
	t_cmd	*cmd;
	t_token	*current;

	cmd = init_cmd();
	current = t;
	while (current && !is_pipe(current))
	{
		if (is_word(current))
			add_arg(&cmd->argv, current->word);
		else if (current->operator == REDIRECT_IN)
			set_infile(current, cmd);
		else if (current->operator == REDIRECT_OUT)
			set_outfile(current, cmd);
		else if (current->operator == REDIRECT_APPEND)
			set_append(current, cmd);
		else if (current->operator == HEREDOC)
			set_heredoc_eof(current, cmd);
		if (current->type == OPERATOR)
			current = current->next;
		if (current)
			current = current->next;
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

// add cmd and transverse until pipe
// if pipe > skip = next
int	parse_argv(t_cmd **head, t_token *t)
{
	t_token	*current;

	current = t;
	while (current)
	{
		add_command(head, new_command(current));
		while (current && !is_pipe(current))
			current = current->next;
		if (current && is_pipe(current))
			current = current->next;
	}
	return (1);
}
