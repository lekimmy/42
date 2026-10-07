/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:16:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/09 18:42:58 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

static void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_sigint = 1;
	rl_catch_signals = 0;
	close(STDIN_FILENO);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}
