/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:15:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/12/22 01:32:30 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buf;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	buf = malloc(size * nmemb);
	if (!buf)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (buf);
	buf = ft_memset(buf, 0, size * nmemb);
	return (buf);
}
