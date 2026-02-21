/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 03:12:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 16:03:39 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Define sig pool
// #define NB_SIG_N
// int	sig[n] = {SIGINT, SIGTERM, SIGHUP};

// Sigaction struct tables to save ongoing handlers
// struct sigaction saves[n];

void	sig_cont(int code)
{
	ft_printf(1, ">>> SIGCONT received %d\n", code);
}

// Force calls on functions logged by atexit
void	sig_term(int code)
{
	ft_printf(2, ">>> SIGTERM received %d\n", code);
	exit(EXIT_SUCCESS);
}

void signal_handler(int signum)
{
	ft_printf(1, "Received SIGINT\n", signum);
	exit(0);
}

// Functions to execute
void exit_function()
{
	ft_printf(1, "Exiting...\n");
}

// Initialize empty signal set
// Add SIGINT to the signal set
// Set sig handler for SIGINT & SIGTERM signals
int	main()
{
	sigset_t	signal_set;
	
	ft_printf(1, "PID = %d\n", getpid());
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	while (1)
	{
		ft_printf(1, "wsh\n");
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

// Log signal handlers
// Sig blocking masks
// int	main(void)
// {
// 	sigset_t	mask;
// 	sigset_t	old;
// 	sigset_t	pending;
// 	char	buf[100];
	
// 	atexit(exit_function());
// 	signal(SIGTERM, &sig_term);
// 	signal(SIGCONT, &sig_cont);
// 	while (true)
// 	{

// 	}
// 	return (EXIT_SUCCESS);
// }