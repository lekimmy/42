/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:16:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/20 19:50:40 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

// malloc len + '\0' + $
static t_exp	*init_exp(char *s, t_env *envs, int exit_code)
{
	t_exp	*exp;
	size_t	len;

	exp = malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	len = expanded_len(s, envs, exit_code);
	exp->buf = malloc(len + 2);
	if (!exp->buf)
		return (NULL);
	exp->i = 0;
	exp->j = 0;
	return (exp);
}

// release expansion state and return ownership of buffer
static char	*finish_exp(t_exp *exp)
{
	char	*expanded;

	expanded = exp->buf;
	free(exp);
	return (expanded);
}

char	*expand_string(char *s, t_env *envs, int exit_code)
{
	size_t	key_len;
	t_exp	*exp;

	exp = init_exp(s, envs, exit_code);
	if (!exp)
		return (NULL);
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
				copy_env_or_key_value(exp, s, key_len, envs);
		}
	}
	exp->buf[exp->j] = '\0';
	return (finish_exp(exp));
}

void	expand_segment(t_segment *seg, t_env *envs, int exit_code)
{
	char	*expand;

	if (seg->quote_context == SINGLE)
		return ;
	expand = expand_string(seg->value, envs, exit_code);
	free(seg->value);
	seg->value = expand;
}
