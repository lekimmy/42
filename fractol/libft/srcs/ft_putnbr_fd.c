/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:52:24 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/18 20:22:03 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int fd, int n)
{
	long int	nb;
	int			tmp;

	nb = n;
	tmp = 0;
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar_fd(fd, '-');
	}
	if (nb >= 10)
		ft_putnbr_fd(fd, nb / 10);
	tmp = nb % 10 + '0';
	ft_putchar_fd(fd, tmp);
}
