/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:02:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/17 20:43:09 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static char	*word(char const *start, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static size_t	word_len(char const *start, char c)
{
	size_t	len;

	len = 0;
	while (*start && *start != c)
	{
		len++;
		start++;
	}
	return (len);
}

static void	free_arr(char **tab_words, size_t i)
{
	while (i > 0)
	{
		free(tab_words[i - 1]);
		i--;
	}
	free(tab_words);
}

// !s == pointer NULL vs. !s[0] || s[0] = '\0' == empty string
char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = word_len(s, c);
			arr[i] = word(s, len);
			if (!arr[i])
				return (free_arr(arr, i), NULL);
			i++;
			s += len;
		}
	}
	return (arr[i] = NULL, arr);
}
