/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 17:00:44 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/10/09 17:00:46 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
fd, fixed BUFFER_SIZE
consume buf[pos], grow line if necessary
stop at \n, return line
*/

// cap *= 2 limits number of reallocs
static char	*grow_line(char *line, int *capacity, int len)
{
	char	*new_line;
	int		i;

	*capacity *= 2;
	new_line = malloc(*capacity);
	if (!new_line)
		return (free(line), NULL);
	i = -1;
	while (++i < len)
		new_line[i] = line[i];
	free(line);
	return (new_line);
}

// if buffer not empty, do not read immediately
// read only when buffer is entirely consumed = refill
// buffer is consistent in-between calls
static int	refill_buffer(int fd, char buf[BUFFER_SIZE], int *bytes_read, int *buf_pos)
{
	if (*buf_pos < *bytes_read)
		return (1);
	*bytes_read = read(fd, buf, BUFFER_SIZE);
	*buf_pos = 0;
	return (*bytes_read > 0);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	bytes_read;
	static int	buf_pos;
	char		*line;
	int			len;
	int			capacity;

	len = 0;
	capacity = 8;
	line = malloc(len);
	if (!line || len == 0)
		return (free(line), NULL);
	while (line && refill_buffer(fd, buf, &bytes_read, &buf_pos))
	{
		if (len + 1 >= capacity)
			line = grow_line(line, &capacity, len);
		if (!line)
			break ;
		line[len] = buf[buf_pos++];
		if (line[len++] == '\n')
			break ;
	}
	line[len] = '\0';
	return (line);
}
