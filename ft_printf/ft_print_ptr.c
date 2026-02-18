/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:45:22 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/18 20:22:59 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Converts any input base
// Needed separate version for unsigned long long
int	ft_print_nb_base_long(unsigned long long n, char *base)
{
	int			base_len;
	int			nb_len;

	base_len = ft_strlen(base);
	nb_len = 0;
	if (n >= (unsigned long long)base_len)
	{
		nb_len += ft_print_nb_base_long(n / base_len, base);
		nb_len += ft_print_nb_base_long(n % base_len, base);
	}
	else
		nb_len += ft_print_char(base[n]);
	return (nb_len);
}

// Converts according to lower or upper case
int	ft_print_hex_long(unsigned long long n, char c)
{
	int	nb_len;

	nb_len = 0;
	if (c == 'x')
		nb_len = ft_print_nb_base_long(n, "0123456789abcdef");
	if (c == 'X')
		nb_len = ft_print_nb_base_long(n, "0123456789ABCDEF");
	return (nb_len);
}

// Converts pointer to unsigned long long
int	ft_print_ptr(void *ptr)
{
	unsigned long long	res;
	int					count_chars;

	if (!ptr)
		return (ft_print_str("(nil)"));
	count_chars = 0;
	res = (unsigned long long)ptr;
	count_chars += ft_print_str("0x");
	count_chars += ft_print_hex_long(res, 'x');
	return (count_chars);
}
