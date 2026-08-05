/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:43:37 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 03:45:03 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid_fov(char *str)
{
	int	i;
	int value;

	i = 0;
	value = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	value = ft_atoi(str);
	if (!is_value_in_range(value, MIN_DEG, MAX_DEG))
		return (0);
	return (1);
}

int	is_valid_coordinates(char **str)
{
	int i;

	i = 0;
	if (str_count(str) != 3)
		return (0);
	while (str[i])
	{
		if (!is_valid_double_format(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_vector(char **vec)
{
	int i;
	int value;

	i = 0;
	value = 0;
	if (str_count(vec) != 3)
		return (0);
	while (vec[i])
	{
		if (!is_valid_double_format(vec[i]))
			return (0);
		if (!is_value_in_range(value, MIN_VECTOR, MAX_VECTOR))
			return (0);
		i++;
	}
	return (1);
}

static int	is_all_digits(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_rgb(char **str)
{
	int	i;
	int	value;

	if (str_count(str) != 3)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!str[i][0] || !is_all_digits(str[i]))
			return (0);
		value = ft_atoi(str[i]);
		if (!is_value_in_range(value, MIN_RGB, MAX_RGB))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_ratio(char *str)
{
	double	ratio;

	ratio = 0;
	if (!is_valid_double_format(str))
		return (0);
	ratio = ft_atof(str);
	if (!is_value_in_range(ratio, MIN_RATIO, MAX_RATIO))
		return (0);
	return (1);
}
