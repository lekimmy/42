/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:30:27 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 23:28:50 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h> // hooks

# include "libft.h"
// # include "get_next_line.h"
# include "mlx.h"
# include "structures.h"
# include "parsing.h"
# include "img.h"

/************************************
 * FREE STR
 *************************************/

void	free_argv(char **str, int size);
void	free_str_arr(char **str);
void	free_str_arr_2(char **s1, char **s2);
void	free_str_arr_3(char **s1, char **s2, char **s3);
void	free_str_arr_4(char **s1, char **s2, char **s3, char **s4);

/************************************
 * FREE OBJS
 *************************************/

void	free_lights(t_light **head);
void	free_spheres(t_sphere **head);
void	free_planes(t_plane **head);
void	free_cylinders(t_cylinder **head);
void	free_scene(t_scene *scene);

/************************************
 * MISC.
 *************************************/

void 	print_error(char *s);

#endif
