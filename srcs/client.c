/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/24 20:52:30 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// 0 sends the signal to every process of the same group
static pid_t	parsing(char *s)
{
	pid_t	pid;

	if (!s || !s[0])
		return (-1);
	pid = ft_atoi(s);
	if (pid <= 0)
	{
		ft_printf(2, "Invalid pid\n");
		return (-1);
	}
	return (pid);
}

// Wrapper function to abstract error handling
static void	KillSignal(pid_t pid, int sigusr)
{
	if (kill(pid, sigusr) == -1)
	{
		ft_printf(2, "Error\n");
		exit(1);
	}
}

// If bit exists, send SIGUSR1 (1)
// else send SIGUSR2 (0)
// kill = send sig
// usleep not to lose any signal
static void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			KillSignal(pid, SIGUSR2);
		else
			KillSignal(pid, SIGUSR1);
		usleep(500);
		bit--;
	}
}

static int valid_process(pid)
{
	if (kill(pid, 0) == -1)
	{
		ft_printf(2, "No such process\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	char	*msg;

	if (argc != 3)
	{
		ft_printf(2, "Usage : ./client pid message\n");
		return (1);
	}
	i = 0;
	msg = argv[2];
	pid = parsing(argv[1]);
	if (!valid_process(pid))
		return (1);
	while (msg[i])
	{
		send_char(pid, msg[i]);
		i++;
	}
	return (0);
}
