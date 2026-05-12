/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:07:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/12 19:27:07 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_test
{
	char	*input;
}			t_test;

char	*token_type_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == TOKEN_REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_HEREDOC)
		return ("EOF");
	return ("UNKNOWN");
}

void	print_tokens(t_token **head)
{
	char	*type_name;
	t_token	*current;

	current = *head;
	while (current)
	{
		type_name = token_type_name(current->type);
		printf("TYPE: %d | TYPE_NAME: %s | VALUE: [%s]\n", current->type, type_name, current->value);
		current = current->next;
	}
}

// NULL = terminating array entry
int main(void)
{
	t_test tests[] = {
		{"echo hello"},
		{"ls|grep hi"},
		{"echo \"hello world\""},
		{"echo \'hello world\'"},
		{"echo abc\"def\"ghi"},
		// {"echo \"undeterminated"},
		{"cat << eof"}, ///
		{NULL}
		// {"          "},
		// {"> >> < << | || >>>> <<<<"},
		// {"ls|grep<><<>>||>>>><<<<hi"} ///
		// {"echo\"hi\""},
		// {"\"hello\"\'world\'\"samere\""},
		// {"wesh\"wesh"},
		// {"wesh\'wesh"},
		// {"wesh\'wesh\'\"yolo"},
		// {"wesh\"wesh\"\'yolo"},
		
	};

	int i = 0;
	while (tests[i].input)
	{
		printf("\ni = %d | INPUT: [%s]\n", i, tests[i].input);
		
		t_token *tokens = NULL;
		
		tokenize(&tokens, tests[i].input);
		// if (tokens == NULL)
		// 	return (1);
		print_tokens(&tokens);
		if (tokens)
			free_all(&tokens);
		i++;
	}
	return (0);
}