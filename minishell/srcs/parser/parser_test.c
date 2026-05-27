/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:52:59 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/27 06:48:37 by ls-phabm         ###   ########.fr       */
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
	t_word		*infile;
	t_word		*outfile;
	t_word		*heredoc_eof;
	t_segment	*seg;
	int			j;
	int			append;
	int			heredoc_expand;
	
	current = *head;
	j = 1;
	while (current)
	{
		arg = current->argv;
		infile = current->infile;
		outfile = current->outfile;
		append = current->append;
		heredoc_eof = current->heredoc_eof;
		heredoc_expand = current->heredoc_expand;
		while (arg)
		{
			seg = arg->segments;
			while (seg)
			{
				printf("j = %d | %s | quote_context = %d\n", j, seg->value, seg->quote_context);
				seg = seg->next;
			}
			arg = arg->next;
		}
		if (infile)
			printf("infile = %s\n", infile->segments->value);
		if (outfile)
			printf("outfile = %s\n", outfile->segments->value);
		if (append)
			printf("append = %d\n", append);
		if (heredoc_eof)
			printf("heredoc_eof = %s\n", heredoc_eof->segments->value);
		if (heredoc_expand)
			printf("heredoc_expand = %d\n", heredoc_expand);
		current = current->next;
		j++;
	}
}

int	main()
{
	t_test	tests[] = {
		{"echo hello"},
		{"cat < file"},
		{"cat << EOF"},
		{"echo $USER > file"},
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
		{"ls | grep test > test.txt | cat test.txt"},
		{"grep particular < text.txt"},
		{"grep particular < text.txt >> test.txt"},
		{"lol >> append"},
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
