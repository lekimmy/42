/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 14:48:47 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/09 14:49:08 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	decimal_calc(char *str, int i)
{
	double	decimal;
	int		j;

	decimal = 0;
	j = 0;
	if (str[i] == '\0')
		return (0);
	while (ft_isdigit(str[i]))
	{
		decimal = (decimal * 10) + (str[i] - '0');
		i++;
		j++;
	}
	decimal = decimal / pow(10, j);
	return (decimal);
}

double	ft_atod(char *str)
{
	double	unit;
	double	decimal;
	double	s;
	int		i;

	i = 0;
	unit = 0;
	s = 1;
	while (is_whitespace(str[i]))
		i++;
	while ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] != '.' && str[i] != '\0')
	{
		unit = (unit * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] =='.')
		i++;
	decimal = decimal_calc(str, i);
	return (s * (unit + decimal));
}
