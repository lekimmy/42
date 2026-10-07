/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:02:19 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/24 17:03:45 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// number of ':'-separated fields, empty ones included ("a::b" -> 3, ":" -> 2)
static int	count_fields(char *s)
{
	int	n;

	n = 1;
	while (*s)
	{
		if (*s == ':')
			n++;
		s++;
	}
	return (n);
}

// POSIX: an empty PATH field means the current directory, so it becomes "."
static char	*dup_field(char *start, size_t len)
{
	if (len == 0)
		return (ft_strdup("."));
	return (ft_substr(start, 0, len));
}

// splits PATH on ':' while KEEPING empty fields, unlike ft_split
char	**split_path(char *path_val)
{
	char	**dirs;
	char	*start;
	int		i;

	dirs = malloc(sizeof(char *) * (count_fields(path_val) + 1));
	if (!dirs)
		return (NULL);
	i = 0;
	start = path_val;
	while (1)
	{
		while (*path_val && *path_val != ':')
			path_val++;
		dirs[i] = dup_field(start, path_val - start);
		if (!dirs[i])
			return (free_strtab(dirs), NULL);
		i++;
		if (!*path_val)
			break ;
		start = ++path_val;
	}
	dirs[i] = NULL;
	return (dirs);
}

// strlen(": command not found\n") + '\0'
char	*join_error(char *cmd)
{
	char	*msg;
	size_t	len;

	len = ft_strlen(cmd);
	msg = malloc(len + 21);
	if (!msg)
		return (NULL);
	ft_memcpy(msg, cmd, len);
	ft_memcpy(msg + len, ": command not found\n", 21);
	return (msg);
}
