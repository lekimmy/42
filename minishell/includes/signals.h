/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/08 19:02:15 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

extern volatile sig_atomic_t	g_sigint;

/************************************
 * SIGNALS
 *************************************/

void	setup_prompt_signals(void);
void	setup_exec_signals(void);
void	setup_wait_signals(void);
void	setup_heredoc_signals(void);
void	restore_prompt_state(void);
void	set_exit_status(t_shell *shell, int status);

#endif