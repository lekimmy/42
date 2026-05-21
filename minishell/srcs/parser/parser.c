/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/21 03:13:36 by ls-phabm         ###   ########.fr       */
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
	while (current)
		current = current->next;
	current->next = word;
}

t_cmd	*new_command(t_token *t)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	while (t && t->operator != PIPE)
	{
		if (is_word(t))
			add_arg(&cmd->argv, t->word);
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

int	parse()
{
	
}