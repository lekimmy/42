/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 23:36:48 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 22:49:57 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	init_vec3(char **str)
{
	t_vec3	vec3;
	
	vec3.x = ft_atof(str[0]);
	vec3.y = ft_atof(str[1]);
	vec3.z = ft_atof(str[2]);
	return (vec3);
}

t_vec3d	init_vec3d(char **str)
{
	t_vec3d	vec3d;

	vec3d.x = ft_atof(str[0]);
	vec3d.y = ft_atof(str[1]);
	vec3d.z = ft_atof(str[2]);
	return (vec3d);
}

t_color	init_rgb(char **str)
{
	t_color	color;

	color.r = ft_atoi(str[0]);
	color.g = ft_atoi(str[1]);
	color.b = ft_atoi(str[2]);
	return (color);
}
