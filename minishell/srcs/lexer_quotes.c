/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/08 21:51:17 by ls-phabm         ###   ########.fr       */
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

// int	in_quotes(char *s, size_t *i)
// {
// 	if (s[*i] == '"')
// 	{
// 		(*i++);
// 		while (s[*i] != '"')
// 			(*i++);
// 		if (s[*i] == '"')
// 			return (1);
// 	}
// 	else if (s[*i] == '\'')
// 	{
// 		(*i++);
// 		while (s[*i] != '\'')
// 			(*i++);
// 		if (s[*i] == '\'')
// 			return (1);
// 	}
// }

void syntax_error(char c)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
}