/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:07:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/12 17:15:21 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_test
{
	char	*input;
}			t_test;

void	print_tokens(t_token *t)
{
	printf("TYPE: %d | VALUE: [%s]\n", t->type, t->value);
}

int main(void)
{
	t_test tests[] = {
		{"echo hello"},
		{"ls|grep hi"},
		{"echo \"hello world\""},
		{"echo \'hello world\'"},
		{"echo abc\"def\"ghi"},
		{"echo \"underterminated"},
		{"cat << eof"},
		{NULL}
	};

	int i =;
	while (tests[i].input)
	{
		printf("\nINPUT: [%s]\n", tests[i].input);
		
		t_token *tokens = NULL;
		
		tokenize(&tokens, tests[i].input);
		print_tokens(tokens);
		free_all(&tokens);
		i++;
	}
}