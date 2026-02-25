/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/25 23:44:54 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Wrapper function to abstract error handling
static void	kill_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_perror("Error\n");
		exit(1);
	}
}

// Decrypt signal received from client as single bit 1 or 0
// Prints char 1 by 1
// - Static bit & char are already initialized at 0
// - Char = 8 bits
// - Decode : each signal is treated to rebuild char until 8 bits
// - Progressive bit shifting
// - Print each single built char
// - Reinitialize bit & char
// - Print \n at message end
// - Send ACK to client after receiving signal
// Use static for variables to survive between signals
static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int				bit;
	static unsigned char	c;

	(void)context;
	c <<= 1;
	if (signal == SIGUSR2)
		c |= 1;
	bit++;
	if (bit == CHAR_BIT)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill_signal(info->si_pid, SIGUSR1);
		}
		else
		{
			write(1, &c, 1);
		}
		bit = 0;
		c = 0;
	}
	kill_signal(info->si_pid, SIGUSR2);
}

// Get process id
// sigaction :
// - Assign signal handler function
// - sa_mask = no signal blocking
// - sa_flags = default behavior
// Set up signal handlers to treat SIGUSR1 & SIGUSR2
// SA_SIGINFO : when delivering signal, also provide extra info about sender
// Pause to wait for signal
int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID = %d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
