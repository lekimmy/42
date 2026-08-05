/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:49:51 by meaba             #+#    #+#             */
/*   Updated: 2026/08/03 21:21:52 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// catch tabs + spaces before newline
int	is_empty_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (*line == '\n' || *line == '\0');
}

// clean line + remove \n
static char *get_next_content_line(int fd)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!is_empty_line(line) && *line != '#')
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

int	read_scene(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_content_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_content_line(fd);
	}
	if (!is_valid_scene(scene))
		return (0);
	return (1);
}
