/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:46:37 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/31 23:33:09 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*gnl_grow(char *line, int *cap, int len)
{
	char	*new;
	int		j;

	*cap *= 2;
	new = malloc(*cap);
	if (!new)
		return (free(line), NULL);
	j = -1;
	while (++j < len)
		new[j] = line[j];
	free(line);
	return (new);
}

static int	gnl_fill(int fd, char buf[BUFFER_SIZE], int *bytes, int *pos)
{
	if (*pos < *bytes)
		return (1);
	*bytes = read(fd, buf, BUFFER_SIZE);
	*pos = 0;
	return (*bytes > 0);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	bytes;
	static int	pos;
	char		*line;
	int			l[2];

	l[0] = 0;
	l[1] = 8;
	line = malloc(l[1]);
	while (line && gnl_fill(fd, buf, &bytes, &pos))
	{
		if (l[0] + 1 >= l[1])
			line = gnl_grow(line, &l[1], l[0]);
		if (!line)
			break ;
		line[l[0]] = buf[pos++];
		if (line[l[0]++] == '\n')
			break ;
	}
	if (!line || l[0] == 0)
		return (free(line), NULL);
	line[l[0]] = '\0';
	return (line);
}
