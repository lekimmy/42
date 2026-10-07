/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:34:32 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/11 18:53:04 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// abstract for read_word()
int	is_separator(char c)
{
	return (ft_isspace(c)
		|| c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '('
		|| c == ')'
		|| c == ';'
	);
}

int	is_unsupported(char c)
{
	return (c == '\\');
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	size_t			total;
	size_t			i;
	unsigned char	*p;

	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
