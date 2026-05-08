/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/09 01:22:13 by ls-phabm         ###   ########.fr       */
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

// first char is quote
// "h"ello"
// h"ello
char	quote_opened(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return ('\0');
}



// any other quote
int	quote_closed(char *s, size_t *i, char c)
{
	while (s[*i])
	{
		if (s[*i] == c)
			return (1);
		(*i)++;
	}
	return (0);
}

size_t	handle_quoted_word(char *s, char *buf, size_t *i, size_t len)
{
	char	quote;
	
	quote = quote_opened(s[*i]);
	(*i)++;
	while (s[*i] && s[*i] != quote)
		buf[len++] = s[(*i)++];
	// buf[j] = '\0';
	if (s[(*i)] != quote)
		return(syntax_error(quote), 0);
	(*i)++;
	return (len);
}

void syntax_error(char c)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
}