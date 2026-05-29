/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:38:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/29 02:57:27 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = get_env_from_envp(envp);
	shell->exit_code = 0;
	shell->pids = NULL;
	shell->interactive = 0;
	return (shell);
}

typedef struct s_test
{
	char	*input;
}			t_test;

void	print_seg(t_cmd **head, t_shell *shell)
{
    t_cmd		*current;
	t_word		*arg;
	t_segment	*seg;
	int			j;
	
	current = *head;
	j = 1;
	while (current)
	{
		arg = current->argv;
		while (arg)
		{
			seg = arg->segments;
			while (seg)
			{
				expand_segment(seg, shell->env, 0);
				printf("j = %d | str = %s\n", j, seg->value);
				seg = seg->next;
			}
			arg = arg->next;
		}
		current = current->next;
		j++;
	}
}

int main(int argc, char **argv, char **envp) {

    t_test	tests[] = {
		{"hello"},
		{"abc\"def\"ghi"},
		{"cat < file"},
		{"cat << EOF"},
		{"echo $USER > file"},
		{"echo $USER"},
		{"echo $HOME"},
		{"echo $SHELL"},
		{"echo $USER$HOME"},
		{"echo $DOES_NOT_EXIST"},
		{"$USERabc"},
		{"$"},
		{"echo $?"}, ///
		{"echo abc$UNKNOWNdef"},
		{"echo $?abc"}, /////////
		{"echo abc$?"},
		{"echo $?$?"},
		{"\"$USER\""},
		{"\'$USER\'"}, //////////
		//// no expansion
		{"echo \'$USER\'"},
		{"echo \'$?\'"},
		{"echo \'abc$USERdef\'"},
		//// expansion
		{"echo \"$USER\""},
		{"echo \"$?\""},
		{"echo \"abc$USERdef\""},
		//// mixed chaos
		{"echo \"\'$USER\'\""},
		{"echo \'\"$USER\"\'"},
		//// adjacent expansions
		{"echo $USER$USER"},
		{"echo $USER$?"}, /////////
		{"echo $?$?"},
		//// invalid var 
		{"echo $42"}, ////////
		{"echo $@"}, ///////
		{"echo $-"},
		{"echo $!"},
		//// edge $ pos
		{"echo $"},
		{"echo abc$"},
		{"echo $$$"},
		//// mixed parsing
		{"echo abc$USERdef"}, ////////
		{"echo $USER]"},
		{"echo [$USER]"},
		{"echo $USER,hello"},
		//// empty / whitespace / weird
		{"echo \"\""},
		{"echo \'\'"},
		{"echo \'    \'"},
		{"echo \"    \""},
		{"echo $\'\'"},
		//// heredoc interaction
		{"cat << EOF \n $USER \n EOF"},
		{"cat << \"EOF\" \n $USER \n EOF"},
		//// stress / combinational traps
		{"echo $USER$USER$USER"},
		{"echo a$b$c$d$e"},
		{"echo $$$$$$"},
		{"echo $USER$?$USER$?"},
		{NULL}
	};
	
	(void)argc;
	(void)argv;
	t_shell	*shell;
	
	shell = init_shell(envp);
	if (!shell)
		return (1);
		
    int i = 0;
	// while (envp[i])
	// 	printf("%s\n", envp[i++]);
	while (tests[i].input)
	{
		printf("\ni = %d | INPUT: [%s]\n", i, tests[i].input);
		
		t_token *tokens = NULL;
		if (tokenize(&tokens, tests[i].input))
		{
			// printf("validate syntax : %d\n", validate_syntax(tokens));
			if (validate_syntax(tokens))
			{
				t_cmd	*cmds = NULL;
				if (parse_argv(&cmds, tokens))
					print_seg(&cmds, shell);
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
