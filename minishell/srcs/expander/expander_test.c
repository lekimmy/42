/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:38:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/26 02:45:22 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_test
{
	char	*input;
}			t_test;

int main() {

    t_test	tests[] = {
		{"hello"},
		{"$USER"},
		{"$USER]"},
		{"$USERabc"},
		{"$"},
		{"$@"},
		{"$?"}, ///
		{"abc$USERdef"},
		{"\"USER\""},
		{"\'USER\'"},
		{NULL}
	};

    int i = 0;
	while (tests[i].input)
	{
		printf("\ni = %d | INPUT: [%s]\n", i, tests[i].input);
		
		t_token *tokens = NULL;
		if (tokenize(&tokens, tests[i].input))
		{
			printf("validate syntax : %d\n", validate_syntax(tokens));
			if (validate_syntax(tokens))
			{
				t_cmd	*cmds = NULL;
				if (parse_argv(&cmds, tokens))
					print_argv(&cmds);
				if (cmds)
				free_cmds(&cmds);
			}
			
		}
		if (tokens)
			free_tokens(&tokens);
		i++;
	}
	return (0);
}
