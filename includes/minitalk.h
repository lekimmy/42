/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:56:16 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/02/21 20:29:46 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "ft_printf.h"
# include "libft.h"
# include <signal.h>

/************************************
 * CLIENT
 ************************************/
int			parsing(char **argv);
int			send_char(int pid, char c);

/************************************
 * SERVER
 ************************************/
static void	handler(int signal);

#endif