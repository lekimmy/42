/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:54:43 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/18 18:34:49 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

int	ft_print_unsigned(int fd, unsigned int n);
int	ft_print_char(int fd, int c);
int	ft_print_str(int fd, char *str);
int	ft_print_perc(void);
int	ft_print_nbr(int fd, int i);
int	ft_print_hex(int fd, unsigned int n, char c);
int	ft_print_ptr(int fd, void *ptr);
int	ft_printf(int fd, const char *format, ...);

#endif