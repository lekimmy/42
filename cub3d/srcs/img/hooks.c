/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 02:56:55 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/11 19:50:13 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Protect in case function is called before any pointer exists
int	close_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->screen.img)
		mlx_destroy_image(game->mlx_conn, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx_conn, game->win);
	if (game->mlx_conn)
	{
		mlx_destroy_display(game->mlx_conn);
		free(game->mlx_conn);
	}
	// free_scene(game->scene);
	close(game->fd);
	exit(0);
}

// // Move with arrow keys
// // Abstraction for norm
// // Steps depend on visible range :
// //		needs to be recomputed everytime
// static int	arrow_handler(int keysym, t_game *game)
// {
// 	double	step;

// 	step = (game->x_max - game->x_min) * NAVIGATION_OFFSET;
// 	if (keysym == XK_Left)
// 	{
// 		game->x_min -= step;
// 		game->x_max -= step;
// 	}
// 	else if (keysym == XK_Right)
// 	{
// 		game->x_min += step;
// 		game->x_max += step;
// 	}
// 	else if (keysym == XK_Up)
// 	{
// 		game->y_min -= step;
// 		game->y_max -= step;
// 	}
// 	else if (keysym == XK_Down)
// 	{
// 		game->y_min += step;
// 		game->y_max += step;
// 	}
// 	// render_fractal(game);
// 	return (0);
// }

// Abstraction for keyboard navigation
// Double space for freeze / unfreeze
// void *param : match the type of callback function
int	key_handler(int keysym, void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	if (keysym == XK_Escape)
		close_handler(game);
	// else if (keysym == XK_space)
	// 	game->locked = !game->locked;
	// else
	// 	arrow_handler(keysym, game);
	return (0);
}
