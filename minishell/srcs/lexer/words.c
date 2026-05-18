/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/18 22:55:02 by ls-phabm         ###   ########.fr       */
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

void	syntax_error_token(char token)
{
	// ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	// ft_putstr_fd(token, 2);
	// ft_putstr_fd("'\n", 2);
	printf("minishell: syntax error near unexpected token '%c'\n", token);
	// return (2);
}

// for expand (different behviors)
// log enum only is enough for semantics
static int	get_quote_type(char quote)
{
	if (quote == DOUBLE_QUOTE)
		return (DOUBLE);
	else if (quote == SINGLE_QUOTE)
		return (SINGLE);
	return (NONE);
}

t_token	*new_token_word(t_segment *segment)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	if (segment)
	{
		token->data.segments = segment;
		if (!token->data.segments)
			return (free(token), NULL);
	}
	token->next = NULL;
	return (token);
}

// must stop at sep = space, |, redirect < >
// *i reference vs. i copy
// *i ptr better for shared reference
// malloc for cleaner memory management
// loop while not separator
// handle quoted & normal segments differently
// returns NULL in case of lexing error
t_token	*handle_word(char *s, size_t *i)
{
	char		*buf;
	int			quote_context;
	size_t		j;
	t_segment	*segment;

	segment = NULL;
	while (s[*i] && !is_separator(s[*i]))
	{
		buf = malloc(ft_strlen(s) + 1);
		if (!buf)
			return (NULL);
		j = 0;
		quote_context = get_quote_type(s[*i]);
		if (quote_context)
		{
			if (!handle_quoted_segment(s, buf, i, &j))
				return (free(buf), free_segments(&segment), NULL);
		}
		else
			handle_normal_segment(s, buf, i, &j);
		buf[j] = '\0';
		add_segment(&segment, new_segment(buf, quote_context));
	}
	return (new_token_word(segment));
}
