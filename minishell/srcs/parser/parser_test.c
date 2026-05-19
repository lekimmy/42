/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:52:59 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/19 05:03:46 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_test
{
	char	*input;
}			t_test;

int	main()
{
	t_test	tests[] = {
		{"echo hello"},
		{"ls|grep hi"},
		{"echo \"hello world\""},
		{"echo \'hello world\'"},
		{"echo abc\"def\"ghi"},
		{"echo \"undeterminated"},
		{"cat << eof"}, ///
		{"          "},
		{"> >> < << | || >>>> <<<<"},
		{"ls|grep<><<>>||>>>><<<<hi"},
		{"echo\"hi\""},
		{"\"hello\"\'world\'\"samere\""},
		{"wesh\"wesh"},
		{"wesh\'wesh"},
		{"wesh\'wesh\'\"yolo"},
		{"wesh\"wesh\"\'yolo"}, /////////////////
		{""},
		{"echo \"\""},
		{"\"\""},
		{"echo ;"},
		{NULL}
	};

	int i = 0;
	while (tests[i].input)
	{
		printf("\ni = %d | INPUT: [%s]\n", i, tests[i].input);
		
		t_token *tokens = NULL;
		// t_cmd	*cmds = NULL;
		if (tokenize(&tokens, tests[i].input))
			printf("validate syntax : %d\n", validate_syntax(tokens));
		if (tokens)
			free_all(&tokens);
		i++;
	}
	return (0);
}
