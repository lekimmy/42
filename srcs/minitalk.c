/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 03:12:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/20 09:53:21 by ls-phabm         ###   ########.fr       */
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

// Functions to execute
void exit_function()
{
	ft_printf(1, "Exiting...\n");
}

int	main()
{
	ft_printf(1, "PID = %d\n", getpid());
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