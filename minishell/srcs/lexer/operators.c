/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/19 03:29:40 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The lexer doesn't see words: it sees chars that slowly become words
// Scan > build > handle quotes inline > emit tokens

// 1. operators + basic words without quotes
// 2. quotes
// 3. edge cases

t_token	*new_token_operator(t_operator_type operator)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = OPERATOR;
	token->operator = operator;
	token->next = NULL;
	return (token);
}

// abstraction to handle operators
// no need to log raw operator, enum for semantics is enough
// return iter jump + token
t_token	*handle_operator(char *s, size_t *i)
{
	if (s[*i] == '|')
		return ((*i)++, new_token_operator(PIPE));
	else if (s[*i] == '>' && s[*i + 1] == '>')
		return ((*i) += 2, new_token_operator(REDIRECT_APPEND));
	else if (s[*i] == '<' && s[*i + 1] == '<')
		return ((*i) += 2, new_token_operator(HEREDOC));
	else if (s[*i] == '<')
		return ((*i)++, new_token_operator(REDIRECT_IN));
	else if (s[*i] == '>')
		return ((*i)++, new_token_operator(REDIRECT_OUT));
	return (NULL);
}
