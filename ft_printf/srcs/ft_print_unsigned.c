/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:03:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/20 07:56:12 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_utoa(unsigned int n)
{
	long int	nb;
	int			len;
	char		*str;

	nb = n;
	len = int_len(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

void	ft_putunbr(int fd, unsigned int n)
{
	long int	nb;
	int			tmp;

	nb = n;
	tmp = 0;
	if (nb >= 10)
		ft_putunbr(fd, nb / 10);
	tmp = nb % 10 + '0';
	ft_putchar_fd(fd, tmp);
}

int	ft_print_unsigned(int fd, unsigned int n)
{
	char	*tab;
	int		count;

	ft_putunbr(fd, n);
	tab = ft_utoa(n);
	count = ft_strlen(tab);
	free(tab);
	return (count);
}
