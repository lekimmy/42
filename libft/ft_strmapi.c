/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:05:31 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/12/22 02:03:15 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*map;
	size_t	i;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	map = malloc(len + 1);
	if (!map)
		return (NULL);
	while (s[i])
	{
		map[i] = f((unsigned int)i, s[i]);
		i++;
	}
	map[i] = '\0';
	return (map);
}
