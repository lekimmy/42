/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:51:00 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/26 00:08:17 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Wrapper function to abstract error handling
void	kill_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_perror("Error\n");
		exit(1);
	}
}
