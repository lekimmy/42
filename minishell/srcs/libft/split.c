/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietri <mpietri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:58:14 by mpietri           #+#    #+#             */
/*   Updated: 2026/05/29 16:58:54 by mpietri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *s, char sep)
{
	int	n;
	int	in_word;

	n = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != sep && !in_word)
		{
			in_word = 1;
			n++;
		}
		else if (*s == sep)
			in_word = 0;
		s++;
	}
	return (n);
}

static char	*next_word(char *s, char sep, size_t *len)
{
	char	*start;

	while (*s && *s == sep)
		s++;
	start = s;
	*len = 0;
	while (*s && *s != sep)
	{
		(*len)++;
		s++;
	}
	return (start);
}

char	**ft_split(char *s, char sep)
{
	char	**res;
	int		n;
	int		i;
	size_t	len;

	n = count_words(s, sep);
	res = malloc(sizeof(char *) * (n + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		s = next_word(s, sep, &len);
		res[i] = ft_substr(s, 0, len);
		if (!res[i])
			return (free_strtab(res), NULL);
		s += len;
		i++;
	}
	res[i] = NULL;
	return (res);
}
