/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 19:17:09 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/11 19:17:51 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_img(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx_conn, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->screen.img)
		return (0);
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp,
			&game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
		return (0);
	return (1);
}

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

static int	rgb_to_int(t_color color)
{
	return ((color.r & 0xFF) << 16 | (color.g & 0xFF) << 8 | (color.b & 0xFF));
}

// test function to play with minilibx
static void	render_test(t_game *game)
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
			my_pixel_put(&game->screen, r.x, r.y, rgb_to_int(color));
			r.x++;
		}
		r.y++;
	}
	mlx_put_image_to_window(game->mlx_conn, game->win, game->screen.img, 0, 0);
}

void	render_game(t_game *game)
{
	render_test(game);
}