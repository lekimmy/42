/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/24 23:39:17 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// static void	signal_handler(int signum)
// {
// 	if (signum == SIGUSR1)
// 		ft_printf(1, "Received bit 0\n");
// 	else if (signum == SIGUSR2)
// 		ft_printf(1, "Received bit 1\n");
// }

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
	static int	bit;
	static char	c;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	c <<= 1;
	if (signal == SIGUSR2)
		c |= 1;
	bit++;
	if (bit == CHAR_BIT)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		kill(client_pid, SIGUSR1);
		bit = 0;
		c = 0;
	}
}

// Get process id
// sigaction :
// - Assign signal handler function
// - sa_mask = no signal blocking
// - sa_flags = default behavior
// Set up signal handlers to treat SIGUSR1 & SIGUSR2
// Pause to wait for signal
int	main(void)
{
	struct sigaction	sa;

	// sigset_t			signal_set;
	ft_printf(1, "PID = %d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}