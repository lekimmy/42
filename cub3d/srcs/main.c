/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 22:37:04 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/11 21:10:35 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	int			fd;
	t_game		game;

	if (argc != 2)
		return (printf("usage: %s <map.cub>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("could not open %s\n", argv[1]), 1);
	if (!init_game(&game, fd))
		return (1);
	render_game(&game);
	mlx_key_hook(game.win, &key_handler, &game);
	mlx_hook(game.win, 17, 0, (void *)close_handler, &game);
	mlx_loop(game.mlx_conn);
	close(fd);
	return (0);
}
