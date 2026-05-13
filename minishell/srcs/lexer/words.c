/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/13 05:07:58 by ls-phabm         ###   ########.fr       */
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

void syntax_error(char c)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
}

// value : don't store literal pointer
// passing string litteral points to read-only memory
// modifying it = crash ; freeing it = UB
// solution : duplicate the string
// = full ownership of memory to free & modify values (expansion)
// init quote_type = 0 [later 1 if '' 2 if ""]
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


// must stop at sep = space, |, redirect < >, EOF
// *i reference vs. i copy
// *i ptr better for shared reference
// malloc for cleaner memory management
// loop while not separator
// handle quoted & normal word differently
// returns empty string in case of lexing error
t_token *handle_word(char *s, size_t *i)
{
	char		*buf;
	char		quote;
	size_t		j;
	t_segment	*segment;
	
	segment = NULL;
	while (s[*i] && !is_separator(s[*i]))
	{
		buf = malloc(ft_strlen(s) + 1);
		if (!buf)
			return (NULL);
		j = 0;
		if ((quote = get_quote_type(s[*i])))
		{
			if (!handle_quoted_segment(s, buf, i, &j))
				return (free(buf), NULL);
		}
		else
			handle_normal_segment(s, buf, i, &j);
		buf[j] = '\0';
		add_segment(&segment, new_segment(buf, quote));
	}
	return (new_token_word(segment));
}
