/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 01:26:44 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 22:56:27 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	free_lights(t_light **head)
{
	t_light	*current;

	if (!head || !(*head))
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free(*head);
		*head = current;
	}
}

void	free_spheres(t_sphere **head)
{
	t_sphere	*current;

	if (!head || !(*head))
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free(*head);
		*head = current;
	}
}

void	free_planes(t_plane **head)
{
	t_plane	*current;

	if (!head || !(*head))
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free(*head);
		*head = current;
	}
}

void	free_cylinders(t_cylinder **head)
{
	t_cylinder	*current;

	if (!head || !(*head))
		return ;
	current = *head;
	while (current)
	{
		current = (*head)->next;
		free(*head);
		*head = current;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->amb)
		free(scene->amb);
	if (scene->cam)
		free(scene->cam);
	if (scene->lights)
		free_lights(&scene->lights);
	if (scene->cylinders)
		free_cylinders(&scene->cylinders);
	if (scene->planes)
		free_planes(&scene->planes);
	if (scene->spheres)
		free_spheres(&scene->spheres);
	free (scene);
}
