/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:18:52 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 09:22:05 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data_julia(t_data *data)
{
	data->max_iter = J_MAX_ITER;
	data->x_min = J_MIN;
	data->x_max = J_MAX;
	data->y_min = J_MIN;
	data->y_max = J_MAX;
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
	data->x_step = data->x_range * X_OFFSET;
	data->y_step = data->y_range * Y_OFFSET;
	data->locked = 0;
}

// Mandelbrot : z starts at 0 ; c varies per px
// Julia : z starts at pixel's coordinates ; c is fixed
void	render_julia(t_data *data)
{
	t_render	r;

	init_render(&r, data);
	while (r.y < WINDOW_HEIGHT)
	{
		r.x = 0;
		while (r.x < WINDOW_WIDTH)
		{
			r.z.x = data->x_min + r.x * r.dx;
			r.z.y = data->y_min + r.y * r.dy;
			r.iter = mandelbrot(&data->c, &r.z, data->max_iter);
			r.color = color_handler(data, r.iter, r.z);
			my_pixel_put(&data->img, r.x, r.y, r.color);
			r.x++;
		}
		r.y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->win, data->img.img, 0, 0);
}

// Map mouse position to a reasonable complex range
// Render the julia set with new c
int	julia_mouse_move(int mouse_x, int mouse_y, void *param)
{
	t_data		*data;
	static int	frame;
	double		dx;
	double		dy;

	data = (t_data *)param;
	if (frame++ % 8 != 0)
		return (0);
	if (data->locked)
		return (0);
	dx = data->x_max / (double)WINDOW_WIDTH;
	dy = data->y_max / (double)WINDOW_HEIGHT;
	data->c.x = data->x_min + dx * (double)mouse_x;
	data->c.y = data->y_min + dy * (double)mouse_y;
	render_julia(data);
	return (0);
}
