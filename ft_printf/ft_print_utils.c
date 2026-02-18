/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:36:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/18 18:21:23 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (ft_strlen("(null)"));
	}
	else
	{
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
}

int	ft_print_perc(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

int	ft_print_nbr(int i)
{
	int		n;

	ft_putnbr_fd(i, 1);
	n = (i <= 0);
	while (i)
	{
		i /= 10;
		n++;
	}
	return (n);
}
