/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:42:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 22:46:22 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

#ifndef IMG_H
# define IMG_H

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define ZOOM_IN 0.9
# define ZOOM_OUT 1.1
# define NAVIGATION_OFFSET 0.03
# define MAX_ZOOM_FACTOR 1e-9

// Canvas to render image & associated pixels
// img = address
// addr = address of the first byte of img buffer
//		returns raw memory [giant byte array]
// bpp = usually 32 = 4 bpp
// endian = how bytes are stored 0 = little (Linux) 1 = big
// line_len : nb of bytes per row in memory
//      !! NOT always WIDTH * (bpp / 8)
//      [how wide each row is in memory]
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img;

typedef struct s_mouse
{
	double		zoom_factor;
	double		x;
	double		y;
}				t_mouse;

typedef struct s_render
{
	int			x;
	int			y;
	double		dx;
	double		dy;
	int			color;
}				t_render;

/************************************
 * MLX
 *************************************/

typedef struct s_data
{
	void		*mlx_conn;
	void		*win;
	int			fd;
	t_scene		*scene;
	t_img		img;
	t_mouse		mouse;
	t_render	render;
	int			locked;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		x_range;
	double		y_range;
	int			max_iter;
	int			*colors;
}				t_data;

int				init_data(t_data *data, int fd);
double			clamp_zoom_factor(double zoom_factor);

/************************************
 * HANDLERS
 *************************************/

int				key_handler(int keysym, void *param);
int				mouse_handler(int button, int px, int py, void *param);
int				close_handler(void *param);

/************************************
 * IMG RENDERING
 *************************************/

double			normalize(int px, int win_size, double min, double max);

void			my_pixel_put(t_img *img, int x, int y, int color);
void			init_render(t_amb *amb, t_data *data);
void			render_scene(t_data *data);

int				create_img(t_data *data);
int				rgb_to_int(t_color color);

#endif