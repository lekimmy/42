/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 22:37:04 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/09 17:47:48 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	int			fd;
	// t_game		game;

	if (argc != 2)
		return (printf("usage: %s <map.cub>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("could not open %s\n", argv[1]), 1);
	printf("lol\n");
	// if (!init_data(&data, fd))
	// 	return (1);
	close(fd);
	return (0);
}
