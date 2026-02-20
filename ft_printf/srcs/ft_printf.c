/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:57:16 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/20 07:55:15 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Input value instead of pointer, otherwise UB
static int	ft_format(int fd, va_list args, const char *format)
{
	if (*format == 'c')
		return (ft_print_char(fd, va_arg(args, int)));
	else if (*format == 's')
		return (ft_print_str(fd, va_arg(args, char *)));
	else if (*format == 'p')
		return (ft_print_ptr(fd, va_arg(args, void *)));
	else if (*format == 'd' || *format == 'i')
		return (ft_print_nbr(fd, va_arg(args, int)));
	else if (*format == 'u')
		return (ft_print_unsigned(fd, va_arg(args, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (ft_print_hex(fd, va_arg(args, unsigned int), *format));
	else if (*format == '%')
		return (ft_print_perc(fd));
	return (-1);
}

// In C standard, printf should stop at invalid or incomplete conversion -> UB
// Must return -1 or ignore safely
// glibc's output is an implementation choice, not a rule
int	ft_handle_percent(int fd, va_list args, const char *format)
{
	int	ret;

	format++;
	if (!format)
		return (va_end(args), -1);
	ret = ft_format(fd, args, (const char *)format);
	if (ret == -1)
		return (-1);
	return (ret);
}

// Reject invalid or incomplete conversion to avoid UB
int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		count_chars;
	int		ret;

	if (!format)
		return (-1);
	count_chars = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			ret = ft_handle_percent(fd, args, (const char *)format);
			if (ret == -1)
				return (va_end(args), -1);
			count_chars += ret;
			format++;
		}
		else
			count_chars += ft_print_char(fd, *format);
		format++;
	}
	return (va_end(args), count_chars);
}
