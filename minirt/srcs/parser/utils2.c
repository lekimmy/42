/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:00:13 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 02:54:43 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"
# include <math.h>

int	is_valid_double_format(char *str)
{
	int	has_dot;
	int	has_number;

	has_dot = 0;
	has_number = 0;
	if ((*str == '-') || (*str == '+'))
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			has_number = 1;
		else if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else
			return (0);
		str++;
	}
	return (has_number);
}

int	is_value_in_range(double value, double min, double max)
{
	return (value >= min && value <= max);
}


static double	decimal_calc(char *str, int i)
{
	double	decimal;
	int		j;

	decimal = 0;
	j = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		decimal = (decimal * 10) + (str[i] - '0');
		i++;
		j++;
	}
	decimal = decimal / pow(10, j);
	return (decimal);
}

// return type : valid 0 vs invalid input
// float vs double
// assumes correct input
// missing decimal point
double	ft_atof(char *str)
{
	double	unit;
	double	decimal;
	double	sign;
	int		i;

	i = 0;
	unit = 0;
	decimal = 0;
	sign = 1;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		unit = (unit * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		decimal = decimal_calc(str, i);
	}
	return (sign * (unit + decimal));
}

// int	ft_atof(char *str, double *result)
// {
// 	int		sign;
// 	double	value;
// 	double	div;

// 	sign = 1;
// 	value = 0;
// 	div = 1;
// 	while (is_whitespace(*str))
//     	str++;
// 	while ((*str == '-') || (*str == '+'))
// 	{
// 		if (*str == '-')
// 			sign = -sign;
// 		str++;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		value = value * 10 + (*str - '0');
// 		str++;
// 	}
// 	if (*str == '.')
// 	{
// 		str++;
// 		while (*str >= '0' && *str <= '9')
// 		{
// 			div *= 10;
// 			value += (*str - '0') / div;
// 			str++;
// 		}
// 	}
// 	*result = value * sign;
// 	return (0);
// }
