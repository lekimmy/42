/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:34:32 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/26 02:41:39 by ls-phabm         ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}