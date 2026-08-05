/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:41:03 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 03:51:26 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 1. check expected number of args
// 2. check each arg format
// 3. check each arg value
// 4. assign to scene->obj
static int	parse_ambient(char *line, t_scene *scene)
{
	char	**amb_str;
	char	**rgb_str;

	if (scene->amb)
		return (print_error("A: already existing ambient\n"), 0);
	amb_str = ft_split(line, ' ');
	if (!amb_str)
		return (0);
	if (str_count(amb_str) != 2)
		return (free_str_arr(amb_str), print_error("A: invalid number of args, expected 2\n"), 0);
	if (!is_valid_ratio(amb_str[0]))
		return (free_str_arr(amb_str), print_error("A: invalid ratio\n"), 0);
	rgb_str = ft_split(amb_str[1], ',');
	if (!rgb_str)
		return (free_str_arr(amb_str), 0);
	if (!is_valid_rgb(rgb_str))
		return (free_str_arr_2(amb_str, rgb_str), print_error("A: invalid rgb\n"), 0);
	scene->amb = init_ambient(amb_str[0], rgb_str);
	if (!scene->amb)
		return (free_str_arr_2(amb_str, rgb_str), print_error("A: malloc failed\n"), 0);
	free_str_arr_2(amb_str, rgb_str);
	return (1);
}

static int	parse_camera(char *line, t_scene *scene)
{
	char	**cam_str;
	char	**pos;
	char	**vec;

	if (scene->cam)
		return (print_error("C: already existing camera\n"), 0);
	cam_str = ft_split(line, ' ');
	if (!cam_str)
		return (0);
	if (str_count(cam_str) != 3)
		return (free_str_arr(cam_str), print_error("C: invalid number of args, expected 3\n"), 0);	
	pos = ft_split(cam_str[0], ',');
	if (!pos)
		return (free_str_arr(cam_str), 0);
	if (!is_valid_coordinates(pos))
		return (free_str_arr_2(cam_str, pos), print_error("C: invalid coordinates\n"), 0);
	vec = ft_split(cam_str[1], ',');
	if (!vec)
		return (free_str_arr_2(cam_str, pos), 0);
	if (!is_valid_vector(vec))
		return (free_str_arr_3(cam_str, pos, vec), print_error("C: invalid vector\n"), 0);
	if (!is_valid_fov(cam_str[2]))
		return (free_str_arr_3(cam_str, pos, vec), print_error("C: invalid fov\n"), 0);
	scene->cam = init_cam(pos, vec, cam_str[2]);
	if (!scene->cam)
		return (free_str_arr_3(cam_str, pos, vec), print_error("C: malloc failed\n"), 0);
	free_str_arr_3(cam_str, pos, vec);
	return (1);
}

static int	parse_light(char *line, t_scene *scene)
{
	char	**light_str;
	char	**pos;
	char	**rgb_str;
	t_light	*light;

	light_str = ft_split(line, ' ');
	if (!light_str)
		return (0);
	if (str_count(light_str) != 2 && str_count(light_str) != 3)
		return (free_str_arr(light_str), print_error("L: invalid number of args, expected 2 or 3\n"), 0);
	pos = ft_split(light_str[0], ',');
	if (!pos)
		return (free_str_arr(light_str), 0);
	if (!is_valid_coordinates(pos))
		return (free_str_arr_2(light_str, pos), print_error("L: invalid coordinates\n"), 0);	
	if (!is_valid_ratio(light_str[1]))
		return (free_str_arr_2(light_str, pos), print_error("L: invalid ratio\n"), 0);
	light = init_light(pos, light_str[1]);
	if (!light)
		return (free_str_arr_2(light_str, pos), print_error("L: malloc failed\n"), 0);
	if (light_str[2])
	{
		rgb_str = ft_split(light_str[2], ',');
		if (!rgb_str)
			return (free_str_arr_2(light_str, pos), 0);
		if (!is_valid_rgb(rgb_str))
			return (free_str_arr_3(light_str, pos, rgb_str), print_error("L: invalid rgb\n"), 0);
		light->color = init_rgb(rgb_str);
		free_str_arr(rgb_str);
	}
	add_light(&scene->lights, light);
	free_str_arr_2(light_str, pos);
	return (1);
}

static int	parse_plane(char *line, t_scene *scene)
{
	char	**plane_str;
	char	**pos;
	char	**vec;
	char	**rgb_str;
	t_plane	*plane;
	
	plane_str = ft_split(line, ' ');
	if (!plane_str)
		return (0);
	if (str_count(plane_str) != 3)
		return (free_str_arr(plane_str), print_error("pl: invalid number of args, expected 3\n"), 0);	
	pos = ft_split(plane_str[0], ',');
	if (!pos)
		return (free_str_arr(plane_str), 0);
	if (!is_valid_coordinates(pos))
		return (free_str_arr_2(plane_str, pos), print_error("pl: invalid coordinates\n"), 0);
	vec = ft_split(plane_str[1], ',');
	if (!vec)
		return (free_str_arr_2(plane_str, pos), 0);
	if (!is_valid_vector(vec))
		return (free_str_arr_3(plane_str, pos, vec), print_error("pl: invalid vector\n"), 0);
	rgb_str = ft_split(plane_str[2], ',');
	if (!rgb_str)
		return (free_str_arr_4(plane_str, pos, vec, rgb_str), 0);
	if (!is_valid_rgb(rgb_str))
		return (free_str_arr_4(plane_str, pos, vec, rgb_str), print_error("pl: invalid rgb\n"), 0);
	plane = init_plane(pos, vec, rgb_str);
	if (!plane)
		return (free_str_arr_4(plane_str, pos, vec, rgb_str), print_error("pl: malloc failed\n"), 0);
	add_plane(&scene->planes, plane);
	free_str_arr_4(plane_str, pos, vec, rgb_str);
	return (1);
}

static int	parse_sphere(char *line, t_scene *scene)
{
	char	**sphere_str;
	char	**pos;
	char	**rgb_str;
	t_sphere	*sphere;
	
	sphere_str = ft_split(line, ' ');
	if (!sphere_str)
		return (0);
	if (str_count(sphere_str) != 3)
		return (free_str_arr(sphere_str), print_error("sp: invalid number of args, expected 3\n"), 0);	
	pos = ft_split(sphere_str[0], ',');
	if (!pos)
		return (free_str_arr(sphere_str), 0);
	if (!is_valid_coordinates(pos))
		return (free_str_arr_2(sphere_str, pos), print_error("sp: invalid coordinates\n"), 0);
	if (!is_valid_double_format(sphere_str[1]))
		return (free_str_arr_2(sphere_str, pos), print_error("sp: invalid diameter\n"), 0);
	rgb_str = ft_split(sphere_str[2], ',');
	if (!rgb_str)
		return (free_str_arr_2(sphere_str, pos), 0);
	if (!is_valid_rgb(rgb_str))
		return (free_str_arr_3(sphere_str, pos, rgb_str), print_error("sp: invalid rgb\n"), 0);
	sphere = init_sphere(pos, sphere_str[1], rgb_str);
	if (!sphere)
		return (free_str_arr_3(sphere_str, pos, rgb_str), print_error("sp: malloc failed\n"), 0);
	add_sphere(&scene->spheres, sphere);
	free_str_arr_3(sphere_str, pos, rgb_str);
	return (1);
}

// skip whitespaces until key char
// parse using str pointer/address, start after key char
int	parse_line(char *line, t_scene *scene)
{
	int	id;

	while (is_whitespace(*line))
		line++;
	id = get_identifier(line);
	if (id == ID_INVALID)
		return (print_error("invalid identifier\n"), 0);
	line += get_id_len(id);
	if (id == ID_AMBIENT)
		parse_ambient(line, scene);
	else if (id == ID_CAMERA)
		parse_camera(line, scene);
	else if (id == ID_LIGHT)
		parse_light(line, scene);
	else if (id == ID_SPHERE)
		parse_sphere(line, scene);
	else if (id == ID_PLANE)
		parse_plane(line, scene);
	else if (id == ID_CYLINDER)
		parse_cylinder(line, scene);
	return (1);
}
