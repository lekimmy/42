/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:16:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/28 22:50:09 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// malloc len + '\0' + $
static t_exp	*init_exp(char *s, int exit_code)
{
	t_exp	*exp;
	size_t	len;

	exp = malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	len = expanded_len(s, exit_code);
	exp->buf = malloc(len + 2);
	if (!exp->buf)
		return (NULL);
	exp->i = 0;
	exp->j = 0;
	return (exp);
}

static char	*expand_string(t_exp *exp, char *s, int exit_code)
{
	size_t	key_len;

	while (s[exp->i])
	{
		if (s[exp->i] != '$')
			exp->buf[exp->j++] = s[exp->i++];
		else if (s[exp->i + 1] == '?')
			copy_exit_code(exp, exit_code);
		else
		{
			key_len = var_len(&s[exp->i + 1]);
			if (!key_len)
				copy_literal_value(exp);
			else
				copy_env_or_key_value(exp, s, key_len);
		}
	}
	exp->buf[exp->j] = '\0';
	return (exp->buf);
}

void	expand_segment(t_segment *seg, int exit_code)
{
	t_exp	*exp;
	char	*expand;

	if (seg->quote_context == 1)
		return ;
	exp = init_exp(seg->value, exit_code);
	expand = expand_string(exp, seg->value, exit_code);
	free(seg->value);
	seg->value = expand;
	free(exp);
}
