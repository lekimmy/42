/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/09 01:29:18 by ls-phabm         ###   ########.fr       */
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

// value : don't store literal pointer
// passing string litteral points to read-only memory
// modifying it = crash ; freeing it = UB
// solution : duplicate the string
// = full ownership of memory to free & modify values (expansion)
t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
	{
		token->value = value;
		if (!token->value)
			return (free(token), NULL);
	}
	token->next = NULL;
	return (token);
}

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

// abstraction to handle operators
// return iter jump + token
static t_token	*handle_operator(char *s, size_t *i)
{
	if (s[*i] == '|')
		return ((*i)++, new_token(TOKEN_PIPE, ft_strdup("|")));
	else if (s[*i] == '>' && s[*i + 1] == '>')
		return ((*i) += 2, new_token(TOKEN_REDIRECT_APPEND, ft_strdup(">>")));
	else if (s[*i] == '<' && s[*i + 1] == '<')
		return ((*i) += 2, new_token(TOKEN_HEREDOC, ft_strdup("<<")));
	else if (s[*i] == '<')
		return ((*i)++, new_token(TOKEN_REDIRECT_IN, ft_strdup("<")));
	else if (s[*i] == '>')
		return ((*i)++, new_token(TOKEN_REDIRECT_OUT, ft_strdup(">")));
	return (NULL);
}

// must stop at sep = space, |, redirect < >, EOF
// *i reference vs. i copy
// *i ptr better for shared reference
// wesh > || . ,,,,      "wesh wesh"
// wesh > wesh >> yolo | ||| | ,,, < <             <<      !!  1 \ ; " wesh wesh"
static t_token *read_word(char *s, size_t *i)
{
	char	*buf;
	size_t	len;
	
	len = 0;
	buf = malloc(ft_strlen(s) + 1);
	if (!buf)
		return (NULL);
	while (s[*i] && !is_separator(s[*i]))
	{
		if (quote_opened(s[*i]))
			len = handle_quoted_word(s, buf, i, len);
		else
		{
			while (s[*i] && !ft_isspace(s[*i]) && !quote_opened(s[*i]))
			{
				buf[len++] = s[(*i)++];
				if (quote_opened(s[*i]))
					break;
			}
		}
	}
	buf[len] = '\0';
	return new_token(TOKEN_WORD, buf);
}

void tokenize(t_token **head, char *s)
{
	size_t		i;
	t_token		*t;

	i = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (is_unsupported(s[i]))
			return (syntax_error(s[i]), free_all(head));
		t = handle_operator(s, &i);
		if (!t)
			t = read_word(s, &i);
		if (t && t->value && t->value[0])
		{
			printf("TYPE: %d | VALUE: [%s]\n", t->type, t->value);
			add_token(head, t);
		}
	}
}
