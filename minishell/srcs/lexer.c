/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:18 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/05 17:53:23 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The lexer doesn't see words: it sees chars that slowly become words
// Scan > build > handle quotes inline > emit tokens
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
	printf("tokenized: %s\n", token->value);
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

static void read_word(char *s)
{
	(void)s;
	return;
}

void tokenize(t_token **head, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			;
		else if (line[i] == '|')
			add_token(head, new_token(TOKEN_PIPE, "|"));
		else if (line[i] == '>' && line[i + 1] == '>')
			add_token(head, new_token(TOKEN_REDIRECT_APPEND, ">>"));
		else if (line[i] == '<' && line[i + 1] == '<')
			add_token(head, new_token(TOKEN_HEREDOC, "<<"));
		else if (line[i] == '<')
			add_token(head, new_token(TOKEN_REDIRECT_IN, "<"));
		else if (line[i] == '>')
			add_token(head, new_token(TOKEN_REDIRECT_OUT, ">"));
		else
			read_word(&line[i]);
		i++;
	}
	printf("You typed: %s\n", line);
}
