/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:42:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/11 19:50:30 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

#include "cub3d.h"
# include <X11/keysym.h> // hooks

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define ZOOM_IN 0.9
# define ZOOM_OUT 1.1
# define NAVIGATION_OFFSET 0.03
# define MAX_ZOOM_FACTOR 1e-9

int		close_handler(void *param);
int		key_handler(int keysym, void *param);

#endif