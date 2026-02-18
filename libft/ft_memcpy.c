/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:29:38 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/11/21 20:29:54 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)dest;
	if (n == 0)
		return (dest);
	if (dest == 0 && src == 0)
		return (NULL);
	while (n != 0)
	{
		*tmp = *(unsigned char *)src;
		tmp++;
		src++;
		n--;
	}
	return (dest);
}
