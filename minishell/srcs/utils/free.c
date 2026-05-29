/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 02:17:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/29 02:24:10 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_segments(t_segment **head)
{
	t_segment	*current;

	if (!head || !(*head))
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free((*head)->value);
		free(*head);
		*head = current;
	}
}

void	free_tokens(t_token **head)
{
	t_token		*current;
	
	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		if ((*head)->type == WORD)
		{
			free_segments(&(*head)->word->segments);
			free((*head)->word);
		}
		free(*head);
		*head = current;
	}
}

void	free_cmds(t_cmd **head)
{
	t_cmd		*current;
	
	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free(*head);
		*head = current;
	}
}

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