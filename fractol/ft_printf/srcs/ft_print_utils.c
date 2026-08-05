/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:36:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/25 22:49:25 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int fd, int c)
{
	ft_putchar_fd(fd, c);
	return (1);
}

int	ft_print_str(int fd, char *str)
{
	if (!str)
	{
		ft_putstr_fd(fd, "(null)");
		return (ft_strlen("(null)"));
	}
	else
	{
		ft_putstr_fd(fd, str);
		return (ft_strlen(str));
	}
}

int	ft_print_perc(int fd)
{
	ft_putchar_fd(fd, '%');
	return (1);
}

int	ft_print_nbr(int fd, int i)
{
	int	n;

	ft_putnbr_fd(fd, i);
	n = (i <= 0);
	while (i)
	{
		i /= 10;
		n++;
	}
	return (n);
}
