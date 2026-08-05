/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 02:56:50 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 11:39:06 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	parsing_error(void)
{
	ft_perror("Usage:\n./fractol mandelbrot\n./fractol tricorn\n");
	ft_perror("./fractol \"burning ship\"\n./fractol julia <x> <y>\n");
}

// Canvas to render image & associated pixels
// addr returns raw memory [giant byte array]
// bpp : usually 32bits = 4 bpp
// line_len : nb of bytes per row in memory
//      !! NOT always WIDTH * (bpp / 8)
//      [how wide each row is in memory]
// endian : how bytes are stored - 0 = little (Linux) 1 = big
// (x, y) >>  address = base + y * line_len + x * (bpp / 8)
//      bpp / 8 [how many bytes one px takes
// Calculate each byte location of px & drop color there
// iter : before divergence
// set up hooks before loop
// ESC with key_handler vs. ad hoc hook for ON_DESTROY (mouse/window)
// Julia hook Motion Notify
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1)
		return (parsing_error(), 1);
	if (!parser_init(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	init_fractal(&data);
	render_fractal(&data);
	mlx_key_hook(data.win, &key_handler, &data);
	mlx_mouse_hook(data.win, &mouse_handler, &data);
	if (data.fractal == JULIA)
		mlx_hook(data.win, 6, 1 << 6, &julia_mouse_move, &data);
	mlx_hook(data.win, 17, 0, &close_handler, &data);
	mlx_loop(data.mlx_conn);
	return (0);
}
