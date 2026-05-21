/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:52:59 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/21 06:30:49 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_test
{
	char	*input;
}			t_test;

void	print_argv(t_cmd **head)
{
	t_cmd		*current;
	t_word		*arg;
	t_segment	*seg;
	
	current = *head;
	while (current)
	{
		arg = current->argv;
		while (arg)
		{
			seg = arg->segments;
			while (seg)
			{
				printf("%s\n", seg->value);
				seg = seg->next;
			}
			arg = arg->next;
		}
		current = current->next;
	}
}

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
		{"echo ;"},
		{"echo\"hi\""},
		{"\"hello\"\'world\'\"samere\""},
		{""},
		{"echo \"\""},
		{"\"\""},
		{"wesh\"wesh"},
		{"wesh\'wesh"},
		{"wesh\'wesh\'\"yolo"},
		{"wesh\"wesh\"\'yolo"}, /////////////////
		// {"ls | grep test > test.txt | cat test.txt"},
		{"grep particular < text.txt >> test.txt"},
		{"ls|grep<><<>>||>>>><<<<hi"},
		{"> >> < << | || >>>> <<<<"},
		{">"},
		{"> test"},
		{"<"},
		{"test <"},
		{">> "},
		{">> test"},
		{" <<"},
		{"test <<"},
		{"|"},
		{"ls || ls"},
		{"ls |"},
		{"| ls"},
		{NULL}
	};

	int i = 0;
	while (tests[i].input)
	{
		printf("\ni = %d | INPUT: [%s]\n", i, tests[i].input);
		
		t_token *tokens = NULL;
		if (tokenize(&tokens, tests[i].input))
			printf("validate syntax : %d\n", validate_syntax(tokens));
		t_cmd	*cmds = NULL;
		if (parse_argv(&cmds, tokens))
			print_argv(&cmds);
		if (tokens)
			free_all(&tokens);
		i++;
	}
	return (0);
}
