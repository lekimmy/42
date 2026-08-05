/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 15:58:29 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 23:12:35 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_error(char *s)
{
	ft_putstr_fd(s, 2);
}

// Program lifecycle :
// 1. Start
// 2. parse args
// 3. init data + scene params
// 4. render
// 5. mouse zoom ?
// 6. update ranges ?
// 7. render again ?

// set up hooks before loop
// ESC with key_handler vs. ad hoc hook for ON_DESTROY (mouse/window)
int main(int argc, char **argv)
{
	int			fd;
	t_data		data;

	if (argc != 2)
		return (printf("usage: %s <scene.rt>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("could not open %s\n", argv[1]), 1);
	if (!init_data(&data, fd))
		return (1);
	render_scene(&data);
	printf("parsing carre\n");
	mlx_key_hook(data.win, key_handler, &data);
	mlx_mouse_hook(data.win, &mouse_handler, &data);
	mlx_hook(data.win, 17, 0, (void *)close_handler, &data);
	mlx_loop(data.mlx_conn);
	close(fd);
	return (0);
}
