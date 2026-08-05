/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:44:46 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/12/22 02:05:22 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;
	size_t	cpy_len;

	i = 0;
	s_len = ft_strlen(s);
	cpy_len = len;
	if (len > s_len - start)
		cpy_len = s_len - start;
	if (start > s_len)
		cpy_len = 0;
	sub = malloc(cpy_len + 1);
	if (!sub)
		return (NULL);
	while (i < cpy_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
