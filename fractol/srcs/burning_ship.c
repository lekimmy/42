/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:18:52 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 08:58:28 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data_bs(t_data *data)
{
	data->max_iter = BS_MAX_ITER;
	data->x_min = BS_MIN;
	data->x_max = BS_MAX;
	data->y_min = BS_MIN;
	data->y_max = BS_MAX;
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
	data->x_step = data->x_range * X_OFFSET;
	data->y_step = data->y_range * Y_OFFSET;
}

// Absolute value applied before squaring
static int	bs(t_complex *c, t_complex *z, int max_iter)
{
	double	tmp_x;
	int		i;
	double	x2;
	double	y2;
	double	xy;

	i = 0;
	while (i < max_iter)
	{
		z->x = fabs(z->x);
		z->y = fabs(z->y);
		x2 = z->x * z->x;
		y2 = z->y * z->y;
		xy = z->x * z->y;
		if (x2 + y2 > 4)
			break ;
		tmp_x = x2 - y2;
		z->y = 2 * xy + c->y;
		z->x = tmp_x + c->x;
		i++;
	}
	return (i);
}

// Mandelbrot : z starts at 0 ; c varies per px
// Julia : z starts at pixel's coordinates ; c is fixed
void	render_bs(t_data *data)
{
	t_render	r;

	init_render(&r, data);
	while (r.y < WINDOW_HEIGHT)
	{
		r.x = 0;
		while (r.x < WINDOW_WIDTH)
		{
			r.c.x = data->x_min + r.x * r.dx;
			r.c.y = data->y_min + r.y * r.dy;
			r.z.x = 0;
			r.z.y = 0;
			r.iter = bs(&r.c, &r.z, data->max_iter);
			r.color = color_handler(data, r.iter, r.z);
			my_pixel_put(&data->img, r.x, r.y, r.color);
			r.x++;
		}
		r.y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->win, data->img.img, 0, 0);
}
