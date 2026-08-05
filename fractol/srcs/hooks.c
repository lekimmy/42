/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 02:56:55 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 09:23:58 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Protect in case function is called before any pointer exists
int	close_handler(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx_conn, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx_conn, data->win);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	exit(0);
}

// Move with arrow keys
static int	arrow_handler(int keysym, t_data *data)
{
	if (keysym == XK_Left)
	{
		data->x_min -= data->x_step;
		data->x_max -= data->x_step;
	}
	else if (keysym == XK_Right)
	{
		data->x_min += data->x_step;
		data->x_max += data->x_step;
	}
	else if (keysym == XK_Down)
	{
		data->y_min += data->y_step;
		data->y_max += data->y_step;
	}
	else if (keysym == XK_Up)
	{
		data->y_min -= data->y_step;
		data->y_max -= data->y_step;
	}
	render_fractal(data);
	return (0);
}

// Abstraction for keyboard navigation
// Double space for freeze / unfreeze
int	key_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_handler(data);
	else if (keysym == XK_space)
		data->locked = !data->locked;
	else
		arrow_handler(keysym, data);
	return (0);
}

static int	update_zoom_range(t_data *data, double x_center, double y_center)
{
	data->x_min = x_center - data->x_range / 2;
	data->x_max = x_center + data->x_range / 2;
	data->y_min = y_center - data->y_range / 2;
	data->y_max = y_center + data->y_range / 2;
	return (0);
}

// Scroll up [4] = zoom in = factor < 1
// Scroll down [5] = zoom out = factor > 1
// [1] Left click [2] Right click [3] Middle click
// 1. Determine zoom factor
// 2. Map mouse coordinates (x, y) to complex plane = new center of the zoom
// 3. Adjust the visible complex range =
//		shrink or expand visible area around mouse
//		the mouse stays at the center of the win = center +/- new_range/2
// 4. Redraw the fractal
// is_rendering = throttle the redraw = skip events if a render is in progress
int	mouse_handler(int button, int mouse_x, int mouse_y, void *param)
{
	t_data		*data;
	double		zoom_factor;
	double		x_center;
	double		y_center;
	static int	is_rendering;

	data = (t_data *)param;
	if (is_rendering)
		return (0);
	is_rendering = 1;
	if (button == 4)
		zoom_factor = ZOOM_IN;
	else if (button == 5)
		zoom_factor = ZOOM_OUT;
	else
		return (is_rendering = 0, 0);
	x_center = normalize(mouse_x, WINDOW_WIDTH, data->x_min, data->x_max);
	y_center = normalize(mouse_y, WINDOW_HEIGHT, data->y_min, data->y_max);
	data->x_range *= zoom_factor;
	data->y_range *= zoom_factor;
	update_zoom_range(data, x_center, y_center);
	render_fractal(data);
	is_rendering = 0;
	return (0);
}
