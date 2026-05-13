/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/13 07:07:31 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// quotes don't split words > they override splitting
// outside quotes, spaces split words
// inside, spaces are just characters

// 1. detect quotes
// 2. read until matching quote
// 3. include content in word
// 4. (ignore expansion for now)
static char	get_quote(char c)
{
	if (c == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	if (c == SINGLE_QUOTE)
		return (SINGLE_QUOTE);
	return ('\0');
}

// log quote: single or double
// move to i real char
// iter to matching quote
// if none then syntax error, return 0
// else move i to next char, return 1
int	handle_quoted_segment(char *s, char *buf, size_t *i, size_t *j)
{
	char	quote;

	quote = get_quote(s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != quote)
		buf[(*j)++] = s[(*i)++];
	if (s[(*i)] != quote)
		return (0);
	(*i)++;
	return (1);
}

void	handle_normal_segment(char *s, char *buf, size_t *i, size_t *j)
{
	while (s[*i] && !is_separator(s[*i]) && !get_quote(s[*i]))
		buf[(*j)++] = s[(*i)++];
}

t_segment	*new_segment(char *value, char quote_context)
{
	t_segment	*segment;

	segment = malloc(sizeof(t_segment));
	if (!segment)
		return (NULL);
	if (value)
	{
		segment->value = value;
		if (!segment->value)
			return (free(segment), NULL);
	}
	segment->quote_context = quote_context;
	segment->next = NULL;
	return (segment);
}

void	add_segment(t_segment **segment, t_segment *new_segment)
{
	t_segment	*current;

	if (!*segment)
	{
		*segment = new_segment;
		return ;
	}
	current = *segment;
	while (current->next)
		current = current->next;
	current->next = new_segment;
}
