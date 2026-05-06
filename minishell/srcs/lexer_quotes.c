/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/06 18:31:01 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	quote_opened()
// {
	
// }

// int	quote_not_closed()
// {
	
// }

void syntax_error(char c)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
}