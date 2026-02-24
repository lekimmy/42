/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/24 18:33:31 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	parsing(char *s)
{
	int	pid;

	if (!s || !s[0])
		return (-1);
	pid = ft_atoi(s);
	if (!ft_isdigit(pid))
		return (-1);
	if (pid <= 0)
		return (-1);
	return (pid);
}

// int	encrpyt_msg(void)
// {
// }

// If bit exists, send SIGUSR1 (1)
// else send SIGUSR2 (0)
// kill = send sig
// usleep not to lose any signal
void	send_char(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;

	if (argc != 3)
		return (1);
	msg = argv[2];
	pid = parsing(argv[1]);
	if (pid < 0)
	{
		exit(EXIT_FAILURE);
		return (1);
	}	
	while (*msg)
	{
		send_char(pid, *msg);
		msg++;
	}
	return (0);
}
