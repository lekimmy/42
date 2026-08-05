/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strlcpy.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: ls-phabm <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/11/11 21:53:50 by ls-phabm  #+##+# */
/*   Updated: 2025/11/11 21:54:41 by ls-phabm ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (siz == 0)
		return (src_len);
	while (src[i] && i < siz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
