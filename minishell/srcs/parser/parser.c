/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/21 08:42:14 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// KISS = identify invalid syntaxes

// 1. if pipe start then error
// 2. if consecutive pipes then error
// 3. if pipe end then error
static int	validate_pipe(t_token *head)
{
	t_token	*current;
	
	if (!head)
		return (0);
	if (is_pipe(head))
		return (0);
	current = head;
	while (current->next)
	{
		if (is_pipe(current) && is_pipe(current->next))
			return (0);
		current = current->next;
	}
	if (is_pipe(current))
		return (0);
	return (1);
}

// if no WORD after redir then error
static int	validate_redirection(t_token *head)
{
	t_token	*current;
	
	if (!head)
		return (0);
	current = head;
	while (current)
	{
		if (is_redir(current))
		{
			if (!current->next)
				return (0);
			if (!is_word(current->next))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

// wrapper
// space only = no token = valid syntax
int	validate_syntax(t_token *head)
{
	if (!head)
		return (1);
	if (!validate_pipe(head))
		return (0);
	if (!validate_redirection(head))
		return (0);
	return (1);
}

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
		return;
	}
	current = *argv;
	while (current->next)
		current = current->next;
	current->next = word;
}

static t_cmd *init_cmd()
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
	cmd->next = NULL;
	return (cmd);
}

void set_infile(t_token *current, t_cmd *cmd)
{
	cmd->infile = current->next->word;
}

void set_outfile(t_token *current, t_cmd *cmd)
{
	cmd->outfile = current->next->word;
}

void set_append(t_token *current, t_cmd *cmd)
{
	cmd->outfile = current->next->word;
	cmd->append = 1;
}

void set_heredoc_eof(t_token *current, t_cmd *cmd)
{
	cmd->heredoc_eof = current->next->word;
}

t_cmd	*new_command(t_token *t)
{
	t_cmd	*cmd;
	t_token	*current;

	cmd = init_cmd();
	current = t;
	while (current && current->operator != PIPE)
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
		if (current)
			current = current->next;
	}
	return (1);
}
