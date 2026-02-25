/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/25 23:06:02 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Protect against no & empty string
// 0 sends the signal to every process of the same group
// Check if process exists
static pid_t	valid_pid(char *s)
{
	pid_t	pid;

	if (!s || !s[0])
		return (0);
	pid = ft_atoi(s);
	if (pid <= 0)
	{
		ft_perror("Invalid pid\n");
		exit(1);
	}
	if (kill(pid, 0) == -1)
	{
		ft_perror("No such process\n");
		exit(1);
	}
	return (pid);
}

// Wrapper function to abstract error handling
static void	kill_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_perror("Error\n");
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
			kill_signal(pid, SIGUSR2);
		else
			kill_signal(pid, SIGUSR1);
		usleep(500);
		bit--;
	}
}

// Send '\0' to signal end of message
int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;
	char	*msg;

	if (argc != 3)
	{
		ft_perror("Usage : ./client <pid> <\"message\">\n");
		return (1);
	}
	i = 0;
	msg = argv[2];
	if (!msg || !msg[0])
		return (1);
	server_pid = valid_pid(argv[1]);
	while (msg[i])
		send_char(server_pid, msg[i++]);
	send_char(server_pid, '\0');
	return (0);
}
