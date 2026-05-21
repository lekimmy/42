/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 04:38:59 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/21 02:52:13 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_token *t)
{
	return (t->type == OPERATOR && t->operator == PIPE);
}

int	is_redir(t_token *t)
{
	return (t->type == OPERATOR && t->operator && t->operator != PIPE);
}

int	is_word(t_token *t)
{
	return (t->type == WORD);
}
