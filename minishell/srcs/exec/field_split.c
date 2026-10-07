/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietri <mpietri@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 16:35:27 by mpietri           #+#    #+#             */
/*   Updated: 2026/06/24 16:35:30 by mpietri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	append_words(t_word **head, t_word *new)
{
	t_word	*cur;

	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

static int	push_segment(t_word **cur, char *val, int quote)
{
	t_segment	*seg;

	if (!val)
		return (1);
	if (!*cur)
	{
		*cur = malloc(sizeof(t_word));
		if (!*cur)
			return (free(val), 1);
		(*cur)->segments = NULL;
		(*cur)->next = NULL;
	}
	seg = new_segment(val, quote);
	if (!seg)
		return (free(val), 1);
	add_segment(&(*cur)->segments, seg);
	return (0);
}

static int	split_value(char *s, t_word **head, t_word **cur)
{
	int		i;
	int		start;

	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
		{
			if (*cur)
				append_words(head, *cur);
			*cur = NULL;
			i++;
		}
		start = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		if (i > start && push_segment(cur, ft_substr(s, start, i - start),
				NONE))
			return (1);
	}
	return (0);
}

static int	split_segments(t_segment *seg, t_word **head, t_word **cur)
{
	while (seg)
	{
		if (seg->quote_context == NONE && seg->value)
		{
			if (split_value(seg->value, head, cur))
				return (1);
		}
		else if (seg->value)
		{
			if (push_segment(cur, ft_strdup(seg->value), seg->quote_context))
				return (1);
		}
		seg = seg->next;
	}
	return (0);
}

t_word	*split_word(t_word *word)
{
	t_word	*head;
	t_word	*cur;

	head = NULL;
	cur = NULL;
	if (split_segments(word->segments, &head, &cur))
	{
		free_word_list(&head);
		free_word_list(&cur);
		return (NULL);
	}
	if (cur)
		append_words(&head, cur);
	return (head);
}
