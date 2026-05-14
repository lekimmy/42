/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:07:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/14 20:23:29 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_test
{
	char	*input;
}			t_test;

char	*token_type_name(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == OPERATOR)
		return ("OPERATOR");
	return ("UNKNOWN");
}

char	*operator_name(t_operator_type type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

char	*operator_raw(t_operator_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == REDIRECT_IN)
		return ("<");
	if (type == REDIRECT_OUT)
		return (">");
	if (type == REDIRECT_APPEND)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	return ("UNKNOWN");
}

void	print_tokens(t_token **head)
{
	char		*type_name;
	char		*operator;
	char		*raw;
	t_token		*current;
	t_segment	*tmp;

	current = *head;
	while (current)
	{
		type_name = token_type_name(current->type);
		if (current->type == OPERATOR)
		{
			operator = operator_name(current->data.operator);
			raw = operator_raw(current->data.operator);
			printf("TYPE: %d | TYPE_NAME: %s | OPERATOR: [%d] | OPERATOR_NAME: %s | RAW: %s\n", 
				current->type, type_name, current->data.operator, operator, raw);
		}
		if (current->type == WORD)
		{
			tmp = current->data.segments;
			while (tmp)
			{
				printf("TYPE: %d | TYPE_NAME: %s | SEGMENT: [%s] | QUOTE_CONTEXT: %d\n", current->type, type_name, tmp->value, tmp->quote_context);
				tmp = tmp->next;
			}
		}
		current = current->next;
	}
}

// NULL = terminating array entry
int main(void)
{
	t_test	tests[] = {
		// {"echo hello"},
		// {"ls|grep hi"},
		// {"echo \"hello world\""},
		// {"echo \'hello world\'"},
		// {"echo abc\"def\"ghi"},
		// {"echo \"undeterminated"},
		// {"cat << eof"}, ///
		// {"          "},
		// {"> >> < << | || >>>> <<<<"},
		// {"ls|grep<><<>>||>>>><<<<hi"},
		{"echo\"hi\""},
		// {"\"hello\"\'world\'\"samere\""},
		// {"wesh\"wesh"},
		// {"wesh\'wesh"},
		// {"wesh\'wesh\'\"yolo"},
		// {"wesh\"wesh\"\'yolo"}, /////////////////
		// {""},
		// {"echo \"\""},
		// {"\"\""},
		{NULL}
	};

	int i = 0;
	while (tests[i].input)
	{
		printf("\ni = %d | INPUT: [%s]\n", i, tests[i].input);
		
		t_token *tokens = NULL;
		
		tokenize(&tokens, tests[i].input);
		print_tokens(&tokens);
		if (tokens)
			free_all(&tokens);
		i++;
	}
	return (0);
}