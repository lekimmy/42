/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:16:20 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/08 19:44:07 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

volatile sig_atomic_t	g_sigint = 0;

// helper for prompt signals
static void	sigint_handler(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Shell = custom handle SIGINT + ignore SIGQUIT
// Parent = restore prompt signals after wait
void	setup_prompt_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Child = default SIGINT + SIGQUIT
void	setup_exec_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

// Parent = ignore SIGINT + SIGQUIT > child treats & dies
void	setup_wait_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_prompt_state(void)
{
	g_sigint = 0;
	rl_done = 0;
	rl_catch_signals = 1;
	setup_prompt_signals();
}
