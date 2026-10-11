/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:42:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/11 21:11:33 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

#include "cub3d.h"
# include <X11/keysym.h> // hooks

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define ZOOM_IN 0.9
# define ZOOM_OUT 1.1
# define NAVIGATION_OFFSET 0.03
# define MAX_ZOOM_FACTOR 1e-9

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_render
{
	int		x;
	int		y;
	double	dx;
	double	dy;
	int		color;
}			t_render;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;


int		close_handler(void *param);
int		key_handler(int keysym, void *param);

void	my_pixel_put(t_img *img, int x, int y, int color);

#endif