/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 21:23:54 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 23:23:17 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

// test function to play with minilibx
static void	render_test(t_data *data)
{
	t_color	color;
	t_render r;

	color.r = 100;
	color.g = 150;
	color.b = 255;

	r.y = 0;
	while (r.y <= WINDOW_HEIGHT)
	{
		r.x = 0;
		while (r.x <= WINDOW_WIDTH)
		{
			my_pixel_put(&data->img, r.x, r.y, rgb_to_int(color));
			r.x++;
		}
		r.y++;
	}
	mlx_put_image_to_window(data->mlx_conn, data->win, data->img.img, 0, 0);
}

void	render_scene(t_data *data)
{
	render_test(data);
}

int	generate_ray(t_cam *cam, double x, double y)
{
	(void)cam;
	(void)x;
	(void)y;
	return (1);
}

// int trace_ray(t_ray ray, t_scene scene)
// {
// 	return (1);
// }

int	shade()
{
	return (1);
}
