/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:26:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/20 19:51:32 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_heredoc	*new_heredoc(t_token *current)
{
	t_heredoc	*hd;

	hd = malloc(sizeof(t_heredoc));
	if (!hd)
		return (NULL);
	hd->eof = current->next->word;
	hd->expand = 0;
	if (current->next->word->segments->quote_context == NONE)
		hd->expand = 1;
	hd->fd = -1;
	hd->next = NULL;
	return (hd);
}

void	heredoc_add_back(t_heredoc **head, t_heredoc *new)
{
	t_heredoc	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
