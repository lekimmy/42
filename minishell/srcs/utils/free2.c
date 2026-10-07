/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 02:17:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/15 16:19:05 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **head)
{
	t_env		*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free(*head);
		*head = current;
	}
}

void	free_heredocs(t_heredoc **head)
{
	t_heredoc	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free_word_list(&(*head)->eof);
		free(*head);
		*head = current;
	}
}

void	free_redirs(t_redir **head)
{
	t_redir	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free_word_list(&(*head)->file);
		free(*head);
		*head = current;
	}
}

void	free_all(char **argv, t_shell *shell)
{
	free_strtab(argv);
	free_shell(shell);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free(shell->line);
	shell->line = NULL;
	free_cmds(&shell->cmd);
	free_env(&shell->env);
	free(shell->pids);
	rl_clear_history();
	free(shell);
}
