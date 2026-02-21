/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:25 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 16:50:28 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int	decrypt_sig(void)
// {
// }

int	main(void)
{
	ft_printf(1, "PID = %d\n", getpid());
	while (1)
	{
		pause();
		exit(EXIT_SUCCESS);
	}
}
