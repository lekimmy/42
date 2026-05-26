/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:12:11 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/27 00:31:26 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;
	size_t	cpy_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		cpy_len = 0;
	else if (len > s_len - start)
		cpy_len = s_len - start;
	else
		cpy_len = len;
	sub = malloc(cpy_len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < cpy_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(char *s)
{
	char		*dup;
	size_t		n;
	size_t		i;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// int	ft_isalnum(int c)
// {
// 	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
// 		return (1);
// 	return (0);
// }

// never dereference input params before validating them, even if n == 0
// encapsulate n == 0 with n--
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;	
	while (n--)
		*d++ = *s++;
	return (dest);
}


char	*ft_itoa(int n)
{
	long int	nb;
	int			len;
	char		*str;

	nb = n;
	len = ft_nbrlen(nb);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (nb)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
