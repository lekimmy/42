/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 22:32:45 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/08/03 03:33:37 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_str_arr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}
void	free_str_arr_2(char **s1, char **s2)
{
	free_str_arr(s1);
	free_str_arr(s2);
}

void	free_str_arr_3(char **s1, char **s2, char **s3)
{
	free_str_arr(s1);
	free_str_arr(s2);
	free_str_arr(s3);
}

void	free_str_arr_4(char **s1, char **s2, char **s3, char **s4)
{
	free_str_arr(s1);
	free_str_arr(s2);
	free_str_arr(s3);
	free_str_arr(s4);
}

void	free_argv(char **str, int size)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free (str);
}
