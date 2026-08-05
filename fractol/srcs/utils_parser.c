/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:16:56 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 11:38:25 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	add_decimal(const char *s, double res)
{
	double	frac;

	frac = 0.1;
	while (*s && *s >= '0' && *s <= '9')
	{
		res += (*s++ - '0') * frac;
		frac /= 10;
	}
	return (res);
}

// Convert string to float
// const char *s = “I promise not to modify the chars that s points to.” > error
//		Always use const char
//			* for string arguments if you don’t need to modify them.
// frac = double = no overflow
// Using int for a div in fractional part limits you to ~9 digits after decimal
// Using double avoids overflow + standard practice for floats
double	ft_atof(const char *s)
{
	double	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
		res = res * 10 + *s++ - '0';
	if (*s == '.')
	{
		s++;
		res = add_decimal(s, res);
	}
	return (res * sign);
}

// Ensure at least 1 digit exists = track bool
// Protect against +., -., .
int	is_valid_float(char *s)
{
	int	dot;
	int	digit;

	dot = 0;
	digit = 0;
	if (*s == '+' || *s == '-')
		s++;
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (*s == '.')
		{
			if (dot)
				return (0);
			dot = 1;
		}
		else if (ft_isdigit(*s))
			digit = 1;
		else
			return (0);
		s++;
	}
	return (digit);
}

int	is_valid_input(char **argv)
{
	double	x;
	double	y;

	if (!is_valid_float(argv[2]) || !is_valid_float(argv[3]))
		return (0);
	x = ft_atof(argv[2]);
	y = ft_atof(argv[3]);
	if (x < J_MIN || x > J_MAX)
		return (0);
	if (y < J_MIN || y > J_MAX)
		return (0);
	return (1);
}

int	parser_init(int argc, char **argv, t_data *data)
{
	if (!ft_strncmp(argv[1], MB_NAME, 10) && argc == MB_ARGC)
		data->fractal = MANDELBROT;
	else if (!ft_strncmp(argv[1], T_NAME, 7) && argc == T_ARGC)
		data->fractal = TRICORN;
	else if (!ft_strncmp(argv[1], BS_NAME, 12) && argc == BS_ARGC)
		data->fractal = BURNING_SHIP;
	else if (!ft_strncmp(argv[1], J_NAME, 5) && argc == J_ARGC)
	{
		if (!is_valid_input(argv))
			return (ft_perror("x and y must be contained in [-1.5 ; 1.5]\n"),
				0);
		data->fractal = JULIA;
		data->c.x = ft_atof(argv[2]);
		data->c.y = ft_atof(argv[3]);
	}
	else
		return (parsing_error(), 0);
	return (1);
}
