/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:31:40 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 22:51:00 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "minirt.h"

typedef enum e_error_type
{
	NO_ERROR,
	ERROR_AMBIENT,
	ERROR_CAMERA,
	ERROR_LIGHT,
	ERROR_SPHERE,
	ERROR_PLANE,
	ERROR_CYLINDER
} t_error_type;

typedef struct s_vec3
{
	double x;
	double y;
	double z;
} t_vec3;

typedef struct s_vec3d // 3D normalized orientation vector. In [-1, 1]
{
	double x;
	double y;
	double z;
} t_vec3d;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_amb
{
	double ratio; // ambient lighting ratio in the range [0.0,1.0]
	t_color color;
} t_amb;

typedef struct s_cam
{
	t_vec3 pos;
	int deg; // FOV: Horizontal field of view in degrees in the range [0,180]
	t_vec3d dim;
} t_cam;

typedef struct s_light
{
	t_vec3 pos;
	double ratio;  // the light brightness ratio in the range [0.0,1.0]
	t_color color; // Not mandatory
	struct s_light *next;
} t_light;

typedef struct s_sphere
{
	t_vec3 pos;
	double d; // sphere diameter
	t_color color;
	struct s_sphere *next;
} t_sphere;

typedef struct s_plane
{
	t_vec3 pos;
	t_vec3d dim;
	t_color color;
	struct s_plane *next;
} t_plane;

typedef struct s_cylinder
{
	t_vec3 pos;
	t_vec3d dim;
	double d; // Cylinder diameter
	double h; // Cylinder height
	t_color color;
	struct s_cylinder *next;
} t_cylinder;

// Exactly 1 A, C
// At least 1 L, sp, pl, cy
typedef struct s_scene
{
	t_amb *amb;
	t_cam *cam;
	t_light *lights;
	t_plane *planes;
	t_sphere *spheres;
	t_cylinder *cylinders;
} t_scene;

#endif
