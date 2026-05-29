/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 04:09:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/29 02:27:51 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return var len
// if 0 > render litteral
// stop at first invalid char and render litteral
size_t	var_len(char *s)
{
	size_t	len;

	len = 0;
	if (!s[len] || (!ft_isalpha(s[len]) && s[len] != '_'))
		return (0);
	while (s[len] && (ft_isalpha(s[len]) || ft_isdigit(s[len])
			|| s[len] == '_'))
		len++;
	return (len);
}

static void	get_expanded_len(size_t *len, char *s, size_t env_len, size_t *i, t_env *envs)
{
	char	*key;
	char	*value;

	key = ft_substr(s, *i + 1, env_len);
	value = env_get(envs, key);
	if (value)
		*len += ft_strlen(value);
	else
		*len += env_len + 1;
	free(key);
	*i += env_len + 1;
}

static void	get_next(size_t *len, size_t *i)
{
	(*len)++;
	(*i)++;
}

static void	get_exit_code_len(size_t *len, size_t *i, int exit_code)
{
	*len += ft_nbrlen(exit_code);
	*i += 2;
}

size_t	expanded_len(char *s, t_env *envs, int exit_code)
{
	size_t	len;
	size_t	env_len;
	size_t	i;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '$')
			get_next(&len, &i);
		else if (s[i + 1] == '?')
			get_exit_code_len(&len, &i, exit_code);
		else
		{
			env_len = var_len(&s[i + 1]);
			if (!env_len)
				get_next(&len, &i);
			else
				get_expanded_len(&len, s, env_len, &i, envs);
		}
	}
	return (len);
}
