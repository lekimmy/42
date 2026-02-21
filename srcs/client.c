/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:39:28 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 19:30:11 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	parsing(char **argv)
{
	int	pid;

	if (!argv[1] || !argv[1][0])
		return (0);
	pid = ft_atoi(argv[1]);
	if (!is_digit(pid))
		return (0);
	if (pid <= 0)
		return (0);
	return (1);
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
	if (!parsing)
		exit(EXIT_FAILURE);
	ft_printf(1, "mdr");
	return (0);
}
