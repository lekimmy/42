/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:06:58 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/11/13 15:07:01 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str);

char	*ft_strrchr(const char *s, int c)
{
	size_t	n;

	c %= 256;
	n = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[n]);
	if (n == 0 || s[0] == '\0')
		return (NULL);
	while (n != 0)
	{
		n--;
		if (s[n] == c)
			return ((char *)&s[n]);
	}
	return (NULL);
}
