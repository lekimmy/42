/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:33:19 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/11 19:23:19 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game, int fd)
{
	game->mlx_conn = mlx_init();
	if (!game->mlx_conn)
		return (0);
	game->win = mlx_new_window(game->mlx_conn, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	if (!game->win)
		return (mlx_destroy_display(game->mlx_conn), free(game->mlx_conn), 0);
	if (!create_img(game))
		return (mlx_destroy_display(game->mlx_conn), free(game->mlx_conn), 0);
	game->fd = fd;
	return (1);
}
