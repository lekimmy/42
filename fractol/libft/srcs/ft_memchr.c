/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:06:58 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/11/13 15:07:01 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*t;

	t = (const unsigned char *)s;
	while (n > 0)
	{
		if (*t == (unsigned char)c)
			return ((void *)t);
		else
		{
			n--;
			t++;
		}
	}
	return (NULL);
}
