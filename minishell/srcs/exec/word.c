/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:38:42 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/22 13:51:52 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static size_t	segs_len(t_segment *seg)
{
	size_t	len;

	len = 0;
	while (seg)
	{
		if (seg->value)
			len += ft_strlen(seg->value);
		seg = seg->next;
	}
	return (len);
}

static void	copy_segs(t_segment *seg, char *res, size_t *j)
{
	while (seg)
	{
		if (seg->value)
		{
			ft_memcpy(res + *j, seg->value, ft_strlen(seg->value));
			*j += ft_strlen(seg->value);
		}
		seg = seg->next;
	}
}

char	*word_to_str(t_word *word)
{
	char	*res;
	size_t	len;
	size_t	j;

	if (!word)
		return (NULL);
	if (!word->segments)
		return (ft_strdup(""));
	len = segs_len(word->segments);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	copy_segs(word->segments, res, &j);
	res[j] = '\0';
	return (res);
}
