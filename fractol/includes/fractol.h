/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 02:35:54 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/03/10 11:39:36 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

/************************************
 * LIBS
 *************************************/

#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
// # include <X11/keysym.h> // hooks
#include <math.h>

/************************************
 * CONST
 *************************************/

typedef enum e_fractal
{
	MANDELBROT = 1,
	JULIA = 2,
	TRICORN = 3,
	BURNING_SHIP = 4
} t_fractal;

/************************************
 * CONST
 *************************************/

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1200
#define ZOOM_IN 0.9
#define ZOOM_OUT 1.1
#define X_OFFSET 0.1
#define Y_OFFSET 0.1

/************************************
 * MANDELBROT
 *************************************/

#define MB_NAME "mandelbrot"
#define MB_ARGC 2
#define MB_MAX_ITER 200
#define MB_XMIN -2.0
#define MB_XMAX 1.0
#define MB_YMIN -1.5
#define MB_YMAX 1.5

/************************************
 * JULIA
 *************************************/

#define J_NAME "julia"
#define J_ARGC 4
#define J_MAX_ITER 100
#define J_MIN -1.5
#define J_MAX 1.5

/************************************
 * TRICORN
 *************************************/

#define T_NAME "tricorn"
#define T_ARGC 2
#define T_MAX_ITER 200
#define T_MIN -2
#define T_MAX 2

/************************************
 * BURNING SHIP
 *************************************/

#define BS_NAME "burning ship"
#define BS_ARGC 2
#define BS_MAX_ITER 200
#define BS_MIN -2
#define BS_MAX 1.5

/************************************
 * STRUCT
 *************************************/

typedef struct s_complex
{
	double x;
	double y;
} t_complex;

typedef struct s_img
{
	void *img;	  // img address
	char *addr;	  // address of the first byte of img buffer
	int bpp;	  // usually 32 = 4 bpp
	int endian;	  // how bytes are stored 0 = little (Linux) 1 = big
	int line_len; // nb of bytes per row in memory
} t_img;

typedef struct s_mouse
{
	double zoom_factor;
	double x;
	double y;
} t_mouse;

typedef struct s_render
{
	int x;
	int y;
	double dx; // px steps
	double dy; // px steps
	t_complex c;
	t_complex z;
	int iter;
	int color;
} t_render;

/************************************
 * MLX
 *************************************/

typedef struct s_data
{
	void *mlx_conn;
	void *win;
	t_fractal fractal;
	t_complex c;
	t_img img;
	t_mouse mouse;
	t_render render;
	int locked;
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double x_range;
	double y_range;
	double x_step;
	double y_step;
	int max_iter;
	int *colors;
} t_data;

/************************************
 * UTILS
 *************************************/

int ft_isdigit(int c);
double ft_atof(const char *s);
int parser_init(int argc, char **argv, t_data *data);
void parsing_error(void);
int init_data(t_data *data);
void init_fractal(t_data *data);
void render_fractal(t_data *data);

/************************************
 * HANDLERS
 *************************************/

int key_handler(int keysym, t_data *data);
int mouse_handler(int button, int px, int py, void *param);
int close_handler(t_data *data);

/************************************
 * IMG RENDERING
 *************************************/

double normalize(int px, int win_size, double min, double max);
void my_pixel_put(t_img *img, int x, int y, int color);
void init_render(t_render *r, t_data *data);
int create_img(t_data *data);
int color_handler(t_data *data, int iter, t_complex z);

/************************************
 * MANDELBROT
 *************************************/
void init_data_mandelbrot(t_data *data);
void render_mandelbrot(t_data *data);
int mandelbrot(t_complex *c, t_complex *z, int max_iter);

/************************************
 * JULIA
 *************************************/
void init_data_julia(t_data *data);
void render_julia(t_data *data);
int julia_mouse_move(int mouse_x, int mouse_y, void *param);

/************************************
 * TRICORN
 *************************************/
void init_data_tricorn(t_data *data);
void render_tricorn(t_data *data);

/************************************
 * BURNING_SHIP
 *************************************/
void init_data_bs(t_data *data);
void render_bs(t_data *data);

#endif