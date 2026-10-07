/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:25:33 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/30 19:44:18 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*op_token_str(t_token *t)
{
	if (t->operator == PIPE)
		return ("|");
	if (t->operator == REDIRECT_IN)
		return ("<");
	if (t->operator == REDIRECT_OUT)
		return (">");
	if (t->operator == REDIRECT_APPEND)
		return (">>");
	if (t->operator == HEREDOC)
		return ("<<");
	return ("newline");
}

int	syntax_error_at(t_token *tok)
{
	if (!tok)
		return (syntax_error("syntax error near unexpected token",
				"newline"), 0);
	return (syntax_error("syntax error near unexpected token",
			op_token_str(tok)), 0);
}

int	is_full_space(char *s)
{
	while (*s)
	{
		if (ft_isspace(*s))
			return (1);
		s++;
	}
	return (0);
}
