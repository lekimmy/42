/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 18:36:21 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Decrypt signal received from client as single bit 1 or 0
// Prints char 1 by 1
// - Initialize bit & char
// - Char = 8 bits
// - Decode : each signal is treated to rebuild char until 8 bits
// - Progressive bit shifting
// - Print each single built char
// - Reinitialize bit & char
// Use static for variables to survive between signals
static void	handler(int signal)
{
	static int	bit;
	static char	c;

	bit = 0;
	c = 0;
	c << 1;
	if (signal == SIGUSR1)
		c |= 1;
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

// Get process id
// Set disposition to treat SIGUSR1 & SIGUSR2 with handler
// Pause to wait for signal
int	main(void)
{
	ft_printf(1, "PID = %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
