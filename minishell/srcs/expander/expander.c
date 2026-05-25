/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:16:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/25 22:33:56 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_env_value(char **env, char *value)
// {
// 	return ("lol");
// }

char	*extract_var(char *str, size_t *i)
{
	
}

size_t	expanded_len(char *s, t_env *env, int exit_code)
{
	while (*s)
	{
		
	}
}

char	*expand_string(char *s, t_env *env, int exit_code);
{
	size_t	i;
	size_t	len;
	char	*buf;
	
	len = expanded_len(s, env, exit_code);
	buf = malloc(len + 1);
	i = 0;
	while ()
	{
		
	}
	buf[i] = '\0';
	return (buf);
}

char	*expand_segment(t_segment *seg, t_env *env, int exit_code)
{
	if (seg->quote_context == 1)
		return ;
	while (seg->value)
	{
		if (*(seg->value) == '$')
			expand_string(seg->value, env, exit_code);
	}
}
