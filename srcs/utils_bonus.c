/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:51:00 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/26 01:56:40 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

// Wrapper function to abstract error handling
void	kill_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_perror("Error\n");
		exit(1);
	}
}

void	init_sigaction(void *handler, int flag)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = flag;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
