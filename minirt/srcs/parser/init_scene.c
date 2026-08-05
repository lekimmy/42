/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 22:55:10 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 22:56:11 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

t_amb	*init_ambient(char *ratio, char **rgb)
{
	t_amb *amb;

	amb = malloc(sizeof(t_amb));
	if (!amb)
		return (NULL);
	amb->ratio = ft_atof(ratio);
	amb->color = init_rgb(rgb);
	return (amb);
}

t_cam	*init_cam(char **pos, char **dim, char *deg)
{
	t_cam	*cam;
	
	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	cam->pos = init_vec3(pos);
	cam->dim = init_vec3d(dim);
	cam->deg = ft_atof(deg);
	return (cam);
}

t_light	*init_light(char **pos, char *ratio)
{
	t_light	*light;
	
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (NULL);
	light->pos = init_vec3(pos);
	light->ratio = ft_atof(ratio);
	light->next = NULL;
	return (light);
}

t_plane	*init_plane(char **pos, char **vec, char **rgb)
{
	t_plane	*plane;
	
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->pos = init_vec3(pos);
	plane->dim = init_vec3d(vec);
	plane->color = init_rgb(rgb);
	plane->next = NULL;
	return (plane);
}

t_sphere	*init_sphere(char **pos, char *d, char **rgb)
{
	t_sphere	*sphere;
	
	sphere = malloc(sizeof(t_plane));
	if (!sphere)
		return (NULL);
	sphere->pos = init_vec3(pos);
	sphere->d = ft_atof(d);
	sphere->color = init_rgb(rgb);
	sphere->next = NULL;
	return (sphere);
}
