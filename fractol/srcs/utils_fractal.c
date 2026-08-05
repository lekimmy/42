/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 02:04:15 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 07:50:56 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	init_data(t_data *data)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		return (0);
	data->win = mlx_new_window(data->mlx_conn, WINDOW_WIDTH, WINDOW_HEIGHT,
			"fractal");
	if (!data->win)
		return (mlx_destroy_display(data->mlx_conn), free(data->mlx_conn), 0);
	if (!create_img(data))
		return (mlx_destroy_display(data->mlx_conn), free(data->mlx_conn), 0);
	return (1);
}

// Init first, render afterwards
// Otherwise every render resets the view = fractal state is constantly reset
// Zoom never survives the render
void	init_fractal(t_data *data)
{
	if (data->fractal == MANDELBROT)
		init_data_mandelbrot(data);
	if (data->fractal == JULIA)
		init_data_julia(data);
	if (data->fractal == TRICORN)
		init_data_tricorn(data);
	if (data->fractal == BURNING_SHIP)
		init_data_bs(data);
}

// Program lifecycle :
// 1. Start
// 2. parse args
// 3. init fractal params
// 4. render
// 5. mouse zoom
// 6. update ranges
// 7. render again
void	render_fractal(t_data *data)
{
	if (data->fractal == MANDELBROT)
		render_mandelbrot(data);
	if (data->fractal == JULIA)
		render_julia(data);
	if (data->fractal == TRICORN)
		render_tricorn(data);
	if (data->fractal == BURNING_SHIP)
		render_bs(data);
}
