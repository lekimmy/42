/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:54:43 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/20 02:57:46 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

int	ft_print_unsigned(unsigned int n);
int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_perc(void);
int	ft_print_nbr(int i);
int	ft_print_hex(unsigned int n, char c);
int	ft_print_ptr(void *ptr);
int	ft_printf(const char *format, ...);

#endif