/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:21:51 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 05:21:05 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

// mlx_put_pixel is too slow
// fill img buffer first before pushing it to window
// protect against inconsistent values = write outside the canvas
// start from img->addr
// y = move to correct row
// x = move to correct col
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

void	init_render(t_render *r, t_data *data)
{
	r->y = 0;
	r->dx = (data->x_max - data->x_min) / (double)WINDOW_WIDTH;
	r->dy = (data->y_max - data->y_min) / (double)WINDOW_HEIGHT;
}

// double log = compress mag, which grows exponentially when point escapes
// when a point escapes, it doesn't explode exactly at iteration but inbetween 2
// log estimates that fractional moment
// normalize that smooth point
// render color
int	color_handler(t_data *data, int iter, t_complex z)
{
	double	smooth;
	double	mag;
	double	t;

	if (iter == data->max_iter)
		return (0xFFFFFF);
	mag = z.x * z.x + z.y * z.y;
	smooth = iter + 1 - log2(log2(mag));
	t = smooth / data->max_iter;
	return ((int)(t * 0xFFFFFF));
}

// Normalize pixel > complex mapping
// !!! px indices are [0, ..., WIDTH - 1] NOT [0, ..., WIDTH]
// init_val = px coordinate (x WIDTH or y HEIGHT)
// init_max = max px of original range (WINDOW_WIDTH or WINDOW_HEIGHT)
// norm_min = min complex value of target range (x_min or y_max)
// norm_max = max complex value of target range (x_max or y_max)
// 1. Scale to 0...1
//      x_scaled = init_val / (init_max - 1)
//      converts px idx into a fraction along [0,1]
// 2. Scale to target range
//      x_range = norm_max - norm_min >> 1.0 - (-2.0) = 3.0
// 3. Multiply fraction by range:
//      x_scaled * x_range
//      At x = 0 → 0 * 3.0 = 0
//      At x = WIDTH-1 → 1 * 3.0 = 3.0
// 4. Shift by minimum
//      mapped = norm_min + (x_scaled * x_range)
//      At x = 0 → -2.0 + 0 = -2.0 ✅
//      At x = WIDTH-1 → -2.0 + 3.0 = 1.0 ✅
double	normalize(int px, int win_size, double min, double max)
{
	return (min + (double)px * (max - min) / (double)(win_size));
}
