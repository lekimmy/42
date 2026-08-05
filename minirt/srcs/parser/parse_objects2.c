/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 01:34:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 03:46:34 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

int	parse_cylinder(char *line, t_scene *scene)
{
	char	**cylinder_str;
	char	**pos;
	char	**vec;
	char	**rgb_str;
	t_cylinder	*cylinder;
	
	cylinder_str = ft_split(line, ' ');
	if (!cylinder_str)
		return (0);
	if (str_count(cylinder_str) != 5)
		return (free_str_arr(cylinder_str), print_error("cy: invalid number of args, expected 3\n"), 0);	
	pos = ft_split(cylinder_str[0], ',');
	if (!pos)
		return (free_str_arr(cylinder_str), 0);
	if (!is_valid_coordinates(pos))
		return (free_str_arr_2(cylinder_str, pos), print_error("cy: invalid coordinates\n"), 0);
	vec = ft_split(cylinder_str[1], ',');
	if (!vec)
		return (free_str_arr_2(cylinder_str, pos), 0);
	if (!is_valid_vector(vec))
		return (free_str_arr_3(cylinder_str, pos, vec), print_error("cy: invalid vector\n"), 0);
	if (!is_valid_double_format(cylinder_str[2]) && !is_valid_double_format(cylinder_str[3]))
		return (free_str_arr_3(cylinder_str, pos, vec), print_error("cy: invalid diameter\n"), 0);
	rgb_str = ft_split(cylinder_str[4], ',');
	if (!rgb_str)
		return (free_str_arr_4(cylinder_str, pos, vec, rgb_str), 0);
	if (!is_valid_rgb(rgb_str))
		return (free_str_arr_4(cylinder_str, pos, vec, rgb_str), print_error("cy: invalid rgb\n"), 0);
	cylinder = init_cylinder(pos, vec, cylinder_str[2], cylinder_str[3], rgb_str);
	if (!cylinder)
		return (free_str_arr_4(cylinder_str, pos, vec, rgb_str), print_error("cy: malloc failed\n"), 0);
	add_cylinder(&scene->cylinders, cylinder);
	free_str_arr_4(cylinder_str, pos, vec, rgb_str);
	return (1);
}
