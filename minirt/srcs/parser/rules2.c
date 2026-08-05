/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:48:11 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 04:03:51 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid_scene(t_scene *scene)
{
	if (!scene->amb)
		return (print_error("missing ambient light\n"), 0);
	if (!scene->cam)
		return (print_error("missing camera\n"), 0);
	if (!scene->lights)
		return (print_error("missing light\n"), 0);
	if (!scene->planes)
		return (print_error("missing plane\n"), 0);
	if (!scene->spheres)
		return (print_error("missing sphere\n"), 0);
	if (!scene->cylinders)
		return (print_error("missing cylinder\n"), 0);
	return (1);
}
