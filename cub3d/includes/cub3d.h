/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 21:59:34 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/09 17:45:15 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

#include "img.h"
#include "parser.h"
#include "mlx.h"

#define BUFFER_SIZE 10

/*
pos, dir, cam
double for raycasting calc precision
*/
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

// grid, dimensions
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
} t_map;

/*
4 walls
mlx img with needed info to read its pixels
*/
typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
} t_textures;

typedef struct s_ray
{
    double	dir_x;
    double	dir_y;
    double	side_dist_x;
    double	side_dist_y;
    double	delta_dist_x;
    double	delta_dist_y;
    double	perp_wall_dist;
    int		map_x;
    int		map_y;
    int		step_x;
    int		step_y;
    int		side;
}	t_ray;

// global entry point
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_player	player;
	t_map		map;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
} t_game;

double	ft_atod(char *str);

#endif