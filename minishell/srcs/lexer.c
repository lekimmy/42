/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/08 19:51:55 by ls-phabm         ###   ########.fr       */
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
		token->value = ft_strdup(value);
		if (!token->value)
			return (free(token), NULL);
	}
	token->quoted = 0;
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
	// printf("%c\n", s[*i]);
	if (s[*i] == '|')
		return ((*i)++, new_token(TOKEN_PIPE, "|"));
	else if (s[*i] == '>' && s[*i + 1] == '>')
		return ((*i) += 2, new_token(TOKEN_REDIRECT_APPEND, ">>"));
	else if (s[*i] == '<' && s[*i + 1] == '<')
		return ((*i) += 2, new_token(TOKEN_HEREDOC, "<<"));
	else if (s[*i] == '<')
		return ((*i)++, new_token(TOKEN_REDIRECT_IN, "<"));
	else if (s[*i] == '>')
		return ((*i)++, new_token(TOKEN_REDIRECT_OUT, ">"));
	return (NULL);
}

// must stop at sep = space, |, redirect < >, EOF
// *i reference vs. i copy
// *i ptr better for shared reference
// wesh > wesh >> yolo | ||| | ,,, < <             <<      !!  1 \ ;
static t_token *read_word(char *s, size_t *i)
{
	size_t		start;
	char		*value;
	char		quote;
	
	printf("__read_word()__\n");
	// start = *i;
	quote = quote_opened(s[*i]);
	
	// printf("%c\n", s[*i]);
	// printf("start = %zu ; i = %zu\n", start, *i);
	if (quote)
	{
		(*i)++;
		start = *i;
		printf("[quote] start = %zu ; i = %zu\n", start, *i);
		while (s[*i] && !is_separator(s[*i]) && (s[*i] != quote))
			(*i)++;
		if (s[*i] == quote)
		{
			// (*i)--;
			printf("[quote_closed] start = %zu ; i = %zu\n", start, *i);
		}
		else
			return(syntax_error(quote), NULL);
	}
	value = ft_substr(s, start, *i - start);
	if (!value || !value[0])
		return (NULL);
	(*i)++;
	// printf("start = %ld --- i = %ld --- value = %s\n", start, *i, value);
	return new_token(TOKEN_WORD, value);
}

void tokenize(t_token **head, char *s)
{
	size_t		i;
	t_token		*t;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i++;
		if (is_unsupported(s[i]))
			return (syntax_error(s[i]), free_all(head));
		t = handle_operator(s, &i);
		if (!t)
			t = read_word(s, &i);
		if (t->value)
		{
			printf("TYPE: %d | VALUE: [%s]\n", t->type, t->value);
			add_token(head, t);
		}
	}
}
