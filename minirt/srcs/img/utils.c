/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:21:51 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 23:19:48 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Init first, render afterwards
// Otherwise every render resets the view = fractal state is constantly reset
// Zoom never survives the render
int init_scene(t_data *data, int fd)
{
	t_scene	*scene;
	
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (0);
	if (!read_scene(fd, scene))
		return (free_scene(scene), 0);
	data->scene = scene;
	return (1);
}

int	init_data(t_data *data, int fd)
{
	data->mlx_conn = mlx_init();
	if (!data->mlx_conn)
		return (0);
	data->win = mlx_new_window(data->mlx_conn, WINDOW_WIDTH, WINDOW_HEIGHT,
			"miniRT");
	if (!data->win)
		return (mlx_destroy_display(data->mlx_conn), free(data->mlx_conn), 0);
	if (!create_img(data))
		return (mlx_destroy_display(data->mlx_conn), free(data->mlx_conn), 0);
	data->fd = fd;
	if (!init_scene(data, fd))
	{
		mlx_destroy_image(data->mlx_conn, data->img.img);
		mlx_destroy_window(data->mlx_conn, data->win);
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
		close(data->fd);
		return (0);
	}
	return (1);
}

double	clamp_zoom_factor(double zoom_factor)
{
	if (zoom_factor < MAX_ZOOM_FACTOR)
		zoom_factor = MAX_ZOOM_FACTOR;
	return (zoom_factor);
}

int	create_img(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx_conn, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img.img)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
		return (0);
	return (1);
}

int	rgb_to_int(t_color color)
{
	return ((color.r & 0xFF) << 16 | (color.g & 0xFF) << 8 | (color.b & 0xFF));
}

// mlx_put_pixel is too slow
// Calculate each byte location of px & drop color there
// fill img buffer first before pushing it to window
// protect against inconsistent values = write outside the canvas
// start from img->addr
// (x, y) >>  address = base + y * line_len + x * (bpp / 8)
// 		y = move to correct row
// 		x = move to correct col
// 		bpp / 8 [how many bytes one px takes]
// write 4 bytes of color
void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (!img || !img->addr)
		return ;
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

// log2 = compress mag, which grows exponentially when point escapes
// when a point escapes, it doesn't explode exactly at iteration but inbetween 2
// log estimates that fractional moment
// normalize that smooth point
// render color
// int	color_handler(t_data *data, int iter, t_complex z)
// {
// 	double	smooth;
// 	double	mag;
// 	double	t;

// 	if (iter == data->max_iter)
// 		return (0xFFFFFF);
// 	mag = z.x * z.x + z.y * z.y;
// 	smooth = iter + 1 - log2(log2(mag));
// 	t = smooth / data->max_iter;
// 	return ((int)(t * 0xFFFFFF));
// }

// Normalize pixel > complex mapping
// !!! px indices are [0, ..., WIDTH - 1] NOT [0, ..., WIDTH]
// px = px coordinate (x WIDTH or y HEIGHT)
// win_size = max px of original range (WINDOW_WIDTH or WINDOW_HEIGHT)
// min = min complex value of target range (x_min or y_max)
// max = max complex value of target range (x_max or y_max)
// 1. Scale to 0...1
//      px_scaled = px / win_size
//      converts px idx into a fraction along [0,1]
// 2. Scale to target range
//      px_range = max - min >> 1.0 - (-2.0) = 3.0
// 3. Multiply fraction by range:
//      px_scaled * px_range
//      At x = 0 → 0 * 3.0 = 0
//      At x = WIDTH-1 → 1 * 3.0 = 3.0
// 4. Shift by minimum
//      mapped = min + (x_scaled * x_range)
//      At x = 0 → -2.0 + 0 = -2.0 ✅
//      At x = WIDTH-1 → -2.0 + 3.0 = 1.0 ✅
double	normalize(int px, int win_size, double min, double max)
{
	return (min + (double)px * (max - min) / (double)(win_size));
}
