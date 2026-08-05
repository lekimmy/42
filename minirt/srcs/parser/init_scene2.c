/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 03:41:08 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 18:19:14 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

t_cylinder	*init_cylinder(char **pos, char **dim, char *d, char *h, char **rgb)
{
	t_cylinder	*cylinder;
	
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->pos = init_vec3(pos);
	cylinder->dim = init_vec3d(dim);
	cylinder->d = ft_atof(d);
	cylinder->h = ft_atof(h);
	cylinder->color = init_rgb(rgb);
	cylinder->next = NULL;
	return (cylinder);
}

