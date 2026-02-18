/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:04:21 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/12/23 21:02:57 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Converts any input base
int	ft_print_nb_base(unsigned int n, char *base)
{
	long	nb;
	int		base_len;
	int		nb_len;

	base_len = ft_strlen(base);
	nb_len = 0;
	nb = n;
	if (nb >= base_len)
	{
		nb_len += ft_print_nb_base(nb / base_len, base);
		nb_len += ft_print_nb_base(nb % base_len, base);
	}
	else
		nb_len += ft_print_char(base[nb]);
	return (nb_len);
}

// Converts according to lower or upper case
int	ft_print_hex(unsigned int n, char c)
{
	int	nb_len;

	nb_len = 0;
	if (c == 'x')
		nb_len = ft_print_nb_base(n, "0123456789abcdef");
	if (c == 'X')
		nb_len = ft_print_nb_base(n, "0123456789ABCDEF");
	return (nb_len);
}
