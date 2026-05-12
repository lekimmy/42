/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/13 01:26:19 by ls-phabm         ###   ########.fr       */
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

char	quote_opened(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return ('\0');
}

void set_quote_type(t_token *t, char quote)
{
	if (quote == '"')
		t->quote_type = 2;
	if (quote == '\'')
		t->quote_type = 1;
}

// log quote: single or double
// move to i real char
// iter to matching quote
// if none then syntax error, return 0
// else move i to next char,r eturn 1
int	handle_quoted_word(char *s, char *buf, size_t *i, size_t *j, char quote)
{
	(*i)++;
	while (s[*i] && s[*i] != quote)
		buf[(*j)++] = s[(*i)++];
	if (s[(*i)] != quote)
		return (0);
	(*i)++;
	return (1);
}

void handle_normal_word(char *s, char *buf, size_t *i, size_t *j)
{
	while (s[*i] && !is_separator(s[*i]) && !quote_opened(s[*i]))
		buf[(*j)++] = s[(*i)++];
}

void syntax_error(char c)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
}