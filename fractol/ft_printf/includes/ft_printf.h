/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:54:43 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/25 22:45:02 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

int	ft_print_unsigned(int fd, unsigned int n);
int	ft_print_char(int fd, int c);
int	ft_print_str(int fd, char *str);
int	ft_print_perc(int fd);
int	ft_print_nbr(int fd, int i);
int	ft_print_hex(int fd, unsigned int n, char c);
int	ft_print_ptr(int fd, void *ptr);
// Keep ft_printf variadic publicly
// Never expose va_list as public API unless intentional
int	ft_printf_fd(int fd, const char *format, ...);
int	ft_printf(const char *format, ...);
int	ft_perror(const char *format, ...);

#endif