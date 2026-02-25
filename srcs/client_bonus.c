/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/24 23:09:22 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// global variable to watch server status
// ** volatile object**
// - its value can be read or modified asynchronously by something other than the current thread of execution
// - its value can be spontanesouly changed by code outside the scope of current code at any time for reasons such as:
// - sharing values with other threads; sharing values with asynchronous signal handlers; accessing hardware devices via memory-mapped I/O
// ** sig_atomic_t **
// - integer type which can be accessed as an atomic entity even in the presence of asynchronous interrupts made by signals.
// - data type that you are allowed to use in the context of a signal handler
// - read the name as "atomic relative to signal handling".
// initiliaze to busy
static volatile sig_atomic_t ack_received = 0;

// Acknowledgement of signal received by server
// End of message received by server
static void ack_end_handler(int signal)
{
	if (signal == SIGUSR1)
		ack_received = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("Message received by server ✅\n");
		exit(0);
	}
}

// Protect against no & empty string
// + 0 = sends the signal to every process of the same group
// Check if process exists
static pid_t valid_pid(char *s)
{
	pid_t pid;

	if (!s || !s[0])
		exit(1);
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
static void KillSignal(pid_t pid, int sigusr)
{
	if (kill(pid, sigusr) == -1)
	{
		ft_perror("Error\n");
		exit(1);
	}
}

// If bit exists, send SIGUSR1 (1)
// else send SIGUSR2 (0)
// reset ACK flag to 0 before sending bit
// kill = send sig
// pause until ACK received vs. usleep
static void send_char(pid_t pid, char c)
{
	int bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			KillSignal(pid, SIGUSR2);
		else
			KillSignal(pid, SIGUSR1);
		bit--;
		while (!ack_received)
			pause();
		ack_received = 0;
	}
}

// Send '\0' to signal end of message
int main(int argc, char **argv)
{
	pid_t server_pid;
	int i;
	char *msg;
	struct sigaction sa;

	if (argc != 3)
	{
		ft_perror("Usage : ./client <pid> <\"message\">\n");
		return (1);
	}
	sa.sa_handler = ack_end_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	msg = argv[2];
	server_pid = valid_pid(argv[1]);
	while (msg[i])
		send_char(server_pid, (unsigned char)msg[i++]);
	send_char(server_pid, '\0');
	return (0);
}
