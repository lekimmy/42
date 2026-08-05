/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 01:12:42 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 03:37:47 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

void	add_light(t_light **lights, t_light *new)
{
	t_light	*current;

	if (!*lights)
	{
		*lights = new;
		return ;
	}
	current = *lights;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_sphere(t_sphere **spheres, t_sphere *new)
{
	t_sphere	*current;

	if (!*spheres)
	{
		*spheres = new;
		return ;
	}
	current = *spheres;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_plane(t_plane **planes, t_plane *new)
{
	t_plane	*current;

	if (!*planes)
	{
		*planes = new;
		return ;
	}
	current = *planes;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_cylinder(t_cylinder **cylinder, t_cylinder *new)
{
	t_cylinder	*current;

	if (!*cylinder)
	{
		*cylinder = new;
		return ;
	}
	current = *cylinder;
	while (current->next)
		current = current->next;
	current->next = new;
}
