/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:53:46 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/02 19:24:47 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// KISS = identify invalid syntaxes
// 1. if pipe start then error
// 2. if consecutive pipes then error
// 3. if pipe end then error
int	validate_pipe(t_token *head)
{
	t_token	*current;

	if (!head)
		return (syntax_error_at(head), 0);
	if (is_pipe(head))
		return (syntax_error_at(head), 0);
	current = head;
	while (current->next)
	{
		if (is_pipe(current) && is_pipe(current->next))
			return (syntax_error_at(current), 0);
		current = current->next;
	}
	if (is_pipe(current))
		return (syntax_error_at(current), 0);
	return (1);
}

// if no WORD after redir then error
int	validate_redirection(t_token *head)
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
				return (syntax_error_at(current->next), 0);
			else if (!is_word(current->next))
				return (syntax_error_at(current->next), 0);
		}
		current = current->next;
	}
	return (1);
}

// reject any unsupported operator first thing
int	reject_unsupported(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == OPERATOR)
		{
			if (current->operator == LPAR)
				return (syntax_error_at(current), 0);
			if (current->operator == RPAR)
				return (syntax_error_at(current), 0);
			if (current->operator == SEMICOL)
				return (syntax_error_at(current), 0);
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
	if (!reject_unsupported(head))
		return (0);
	if (!validate_pipe(head))
		return (0);
	if (!validate_redirection(head))
		return (0);
	return (1);
}
