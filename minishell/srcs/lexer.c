/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/06 16:57:37 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The lexer doesn't see words: it sees chars that slowly become words
// Scan > build > handle quotes inline > emit tokens

// 1. operators + basic words without quotes
// 2. quotes
// 3. edge cases

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

static t_token	*handle_operator(char *s, size_t *i)
{
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
// wesh > wesh >> yolo | ||| | ,,, < <             <<      !!  1
static t_token *read_word(char *s, size_t *i)
{
	size_t		start;
	char		*value;
	
	start = *i;
	while (s[*i] && !is_separator(s[*i]))
		(*i)++;
	value = ft_substr(s, start, *i - start);
	if (!value || !value[0])
		return (NULL);
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
