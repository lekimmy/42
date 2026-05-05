/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/05 22:55:03 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The lexer doesn't see words: it sees chars that slowly become words
// Scan > build > handle quotes inline > emit tokens

// 1. operators + basic words without quotes
// 2. quotes
// 3. edge cases

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
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

static int	is_separator(char c)
{
	return (ft_isspace(c) || c == '|' || c == '<' || c == '>');
}

// must stop at sep = space, |, redirect < >, EOF
// *i reference vs. i copy
static t_token *read_word(char *s, size_t *i)
{
	size_t		start;
	char	*value;
	
	start = *i;
	while (s[*i] && !is_separator(s[*i]))
		(*i)++;
	// printf("start = %ld --- i = %ld\n", start, *i);
	value = ft_substr(s, start, *i - start);
	if (!value)
		return (NULL);
	return new_token(TOKEN_WORD, value);
}

void tokenize(t_token **head, char *line)
{
	size_t		i;
	t_token		*t;

	i = 0;
	while (line[i])
	{
		t = NULL;
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
		{
			t = new_token(TOKEN_PIPE, "|");
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			t = new_token(TOKEN_REDIRECT_APPEND, ">>");
			i += 2;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			t = new_token(TOKEN_HEREDOC, "<<");
			i += 2;
		}
		else if (line[i] == '<')
		{
			t = new_token(TOKEN_REDIRECT_IN, "<");
			i++;
		}
		else if (line[i] == '>')
		{
			t = new_token(TOKEN_REDIRECT_OUT, ">");
			i++;
		}
		else
			t = read_word(line, &i);
		if (t)
		{
			printf("TYPE: %d | VALUE: [%s]\n", t->type, t->value);
			add_token(head, t);
		}
	}
}
