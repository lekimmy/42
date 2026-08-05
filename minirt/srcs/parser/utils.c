/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 21:07:30 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 02:54:49 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	str_count(char **str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

// get id to parse associated line / object
int	get_identifier(char *line)
{
	int	i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (line[i] == 'A' && is_whitespace(line[i+1]))
		return (ID_AMBIENT);
	else if (line[i] == 'C' && is_whitespace(line[i+1]))
		return (ID_CAMERA);
	else if (line[i] == 'L' && is_whitespace(line[i+1]))
		return (ID_LIGHT);
	else if (line[i] == 's' && line[i + 1] == 'p' && is_whitespace(line[i+2]))
		return (ID_SPHERE);
	else if (line[i] == 'p' && line[i + 1] == 'l' && is_whitespace(line[i+2]))
		return (ID_PLANE);
	else if (line[i] == 'c' && line[i + 1] == 'y' && is_whitespace(line[i+2]))
		return (ID_CYLINDER);
	else
		return (ID_INVALID);
}

int	get_id_len(int id)
{
	if (id == ID_AMBIENT || id == ID_CAMERA || id == ID_LIGHT)
		return (1);
	if (id == ID_SPHERE || id == ID_PLANE || id == ID_CYLINDER)
		return (2);
	return (0);
}

// char	**fig_str_split(char *str)
// {
// 	char	**out;

// 	if (!str)
// 		return (NULL);
// 	out = ft_split(str, ' ');
// 	if (!out)
// 		return (NULL);
// 	return (out);
// }

// char	**three_values_split(char *str)
// {
// 	char	**out;

// 	if (!str)
// 		return (NULL);
// 	out = ft_split(str, ',');
// 	if (!out)
// 		return (NULL);
// 	return (out);
// }

// int	pl_values_treatment(char **str, t_pl *pl)
// {
// 	char	**out;

// 	out = ft_split(str[0], ',');
// 	if (!out)
// 		return (1);
// 	vec3_parsing(out, &pl->pos);
// 	free(out);
// 	out = ft_split(str[1], ',');
// 	if (!out)
// 		return (1);
// 	vec3d_parsing(out, &pl->dim);
// 	free(out);
// 	if (vec3d_value_check(pl->dim))
// 		return (1);
// 	out = ft_split(str[2], ',');
// 	if (!out)
// 		return (1);
// 	rgb_parsing(out, &pl->color);
// 	free(out);
// 	if (rgb_value_check(pl->color))
// 		return (1);
// 	return (0);
// }

// int	sp_values_treatment(char **str, t_sp *sp)
// {
// 	char	**out;

// 	out = ft_split(str[0], ',');
// 	if (!out)
// 		return (1);
// 	vec3_parsing(out, &sp->pos);
// 	free(out);
// 	sp->d = ft_atof(str[1]);
// 	out = ft_split(str[2], ',');
// 	if (!out)
// 		return (1);
// 	rgb_parsing(out, &sp->color);
// 	free(out);
// 	if (rgb_value_check(sp->color))
// 		return (1);
// 	return (0);
// }

// int	cy_values_treatment(char **str, t_cy *cy)
// {
// 	char	**out;

// 	out = ft_split(str[0], ',');
// 	if (!out)
// 		return (1);
// 	vec3_parsing(out, &cy->pos);
// 	free(out);
// 	out = ft_split(str[1], ',');
// 	if (!out)
// 		return (1);
// 	vec3d_parsing(out, &cy->dim);
// 	free(out);
// 	if (vec3d_value_check(cy->dim))
// 		return (1);
// 	cy->d = ft_atof(str[2]);
// 	cy->h = ft_atof(str[3]);
// 	out = ft_split(str[4], ',');
// 	if (!out)
// 		return (1);
// 	rgb_parsing(out, &cy->color);
// 	free(out);
// 	if (rgb_value_check(cy->color))
// 		return (1);
// 	return (0);
// }