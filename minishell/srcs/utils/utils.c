/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:34:32 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/14 20:39:32 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// abstract for read_word()
int	is_separator(char c)
{
	return (ft_isspace(c) || c == '|' || c == '<' || c == '>');
}

int	is_unsupported(char c)
{
	return ((c == '\\') || (c == ';'));
}

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

void	free_all(t_token **head)
{
	t_token		*current;
	
	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		if ((*head)->type == WORD)
			free_segments(&(*head)->data.segments);
		free(*head);
		*head = current;
	}
}
