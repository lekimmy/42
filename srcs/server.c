/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 17:50:18 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Decrypt signal received from client as bit 1 or 0
// Char = 8 bits
// Initialize bit & char
// Decode and print each char one by one
// Reinitialize bit & char
static void	handler(int signal)
{
	static int	bit;
	static char	c;

	bit = 0;
	c = 0;
	if (signal == SIGUSR1)
		// decryption logic
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
