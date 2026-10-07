/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:16:15 by mpietri           #+#    #+#             */
/*   Updated: 2026/06/20 19:49:36 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static void	expand_word(t_word *word, t_env *env, int exit_code)
{
	t_segment	*seg;

	if (!word)
		return ;
	seg = word->segments;
	while (seg)
	{
		expand_segment(seg, env, exit_code);
		seg = seg->next;
	}
}

static void	expand_word_list(t_word *word, t_env *env, int exit_code)
{
	while (word)
	{
		expand_word(word, env, exit_code);
		word = word->next;
	}
}

// rebuild argv applying word splitting on unquoted expansions
static void	split_argv(t_cmd *cmd)
{
	t_word	*new_head;
	t_word	*word;
	t_word	*pieces;
	t_word	*next;

	new_head = NULL;
	word = cmd->argv;
	while (word)
	{
		next = word->next;
		word->next = NULL;
		pieces = split_word(word);
		free_word_list(&word);
		append_words(&new_head, pieces);
		word = next;
	}
	cmd->argv = new_head;
}

static void	expand_cmd(t_cmd *cmd, t_env *env, int exit_code)
{
	expand_word_list(cmd->argv, env, exit_code);
	expand_word_list(cmd->infile, env, exit_code);
	expand_word_list(cmd->outfile, env, exit_code);
	split_argv(cmd);
}

void	expand_cmds(t_shell *shell, t_cmd *cmd)
{
	while (cmd)
	{
		expand_cmd(cmd, shell->env, shell->exit_code);
		cmd = cmd->next;
	}
}
