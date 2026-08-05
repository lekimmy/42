/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:53:57 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 22:50:11 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

/************************************
 * CONSTS
 *************************************/

# define BUFFER_SIZE 10

# define MIN_RGB 0
# define MAX_RGB 255
# define MIN_RATIO 0.0
# define MAX_RATIO 1.0
# define MIN_DEG 0
# define MAX_DEG 180
# define MIN_VECTOR -1
# define MAX_VECTOR 1

typedef enum e_identifier
{
	ID_INVALID,
	ID_AMBIENT,
	ID_CAMERA,
	ID_LIGHT,
	ID_SPHERE,
	ID_PLANE,
	ID_CYLINDER
}	t_identifier;

/************************************
 * UTILS
 *************************************/

int	is_whitespace(char c);
int	get_identifier(char *line);
int	get_id_len(int id);
int	str_count(char **str);

double	ft_atof(char *str);

/************************************
 * STR
 *************************************/

char	*get_next_line(int fd);

int	parse_line(char *line, t_scene *scene);
int	read_scene(int fd, t_scene *scene);

/************************************
 * RULES
 *************************************/

int	is_value_in_range(double value, double min, double max);
int	is_valid_double_format(char *str);
int	is_valid_rgb(char **str);
int	is_valid_ratio(char *str);
int	is_valid_coordinates(char **str);
int	is_valid_fov(char *str);
int	is_valid_vector(char **vec);
int	is_valid_scene(t_scene *scene);

int	parse_cylinder(char *line, t_scene *scene);

/************************************
 * INIT
 *************************************/

t_vec3	init_vec3(char **str);
t_vec3d	init_vec3d(char **str);
t_color	init_rgb(char **str);

t_amb	*init_ambient(char *ratio, char **rgb);
t_cam	*init_cam(char **pos, char **dim, char *deg);
t_light	*init_light(char **pos, char *ratio);
t_plane	*init_plane(char **pos, char **vec, char **rgb);
t_sphere	*init_sphere(char **pos, char *d, char **rgb);
t_cylinder	*init_cylinder(char **pos, char **vec, char *d, char *h, char **rgb);

void	add_light(t_light **lights, t_light *new);
void	add_sphere(t_sphere **spheres, t_sphere *new);
void	add_plane(t_plane **planes, t_plane *new);
void	add_cylinder(t_cylinder **cylinder, t_cylinder *new);

#endif
