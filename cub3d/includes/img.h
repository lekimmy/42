/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:42:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/09 19:09:45 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

#include "cub3d.h"

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define ZOOM_IN 0.9
# define ZOOM_OUT 1.1
# define NAVIGATION_OFFSET 0.03
# define MAX_ZOOM_FACTOR 1e-9

// Canvas to render image & associated pixels
// img = address
// addr = address of the first byte of img buffer
//		returns raw memory [giant byte array]
// bpp = usually 32 = 4 bpp
// endian = how bytes are stored 0 = little (Linux) 1 = big
// line_len : nb of bytes per row in memory
//      !! NOT always WIDTH * (bpp / 8)
//      [how wide each row is in memory]

typedef struct s_mouse
{
	double		zoom_factor;
	double		x;
	double		y;
}				t_mouse;

typedef struct s_render
{
	int			x;
	int			y;
	double		dx;
	double		dy;
	int			color;
}				t_render;

#endif