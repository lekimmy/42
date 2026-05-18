/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/19 01:30:25 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The lexer doesn't see words: it sees chars that slowly become words
// Scan > build > handle quotes inline > emit tokens

// 1. operators + basic words without quotes
// 2. quotes
// 3. edge cases

// unclosed quotes + special chars / unsupported ops (\;) = syntax error
// closer to bash + avoids UB later + easier than trying to support them

// linked list
static void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

// only spaces = no token
// "" = valid token (quoted)
// no token, no token value, or value is null = buggy == free all
// else add token
int	tokenize(t_token **head, char *s)
{
	size_t		i;
	t_token		*t;

	i = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		if (is_unsupported(s[i]))
			return (lexer_error("unexpected token", &s[i]), 0);
		t = handle_operator(s, &i);
		if (!t)
			t = handle_word(s, &i);
		if (!t)
			return (0);
		add_token(head, t);
	}
	return (1);
}
