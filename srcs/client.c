/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 18:42:59 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	is_valid_pid(int pid)
{
	if (pid > 0)
		return (1);
	return (0);
}

int	parsing(void)
{
}

int	encrpyt_msg(void)
{
}

int	send_msg(void)
{
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	if (!is_valid_pid(argv[1]))
		exit(EXIT_FAILURE);
	ft_printf(1, "mdr");
	return (0);
}
