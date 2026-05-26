/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:16:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/26 03:34:56 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return var len
// if 0 > render litteral
// stop at first invalid char and render litteral
static size_t	var_len(char *s)
{
	size_t	len;

	len = 0;
	if (!s[len] || (!ft_isalpha(s[len]) && s[len] != '_'))
		return (0);
	while (s[len] && (ft_isalpha(s[len]) || ft_isdigit(s[len])))
		len++;
	return (len);
}

size_t	expanded_len(char *s, int exit_code)
{
	size_t	len;
	size_t	env_len;
	size_t	i;
	char	*key;
	char	*env;
	
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '$')
		{
			len++;
			i++;
		}	
		else if (s[i + 1] == '?')
		{
			len += ft_nbrlen(exit_code);
			i += 2;
			continue;
		}
		else
		{
			env_len = var_len(&s[i + 1]);
			printf("env_len = %ld\n", env_len);
			if (!env_len)
			{
				len++;
				i++;
			}
			else
			{
				key = ft_substr(s, i + 1, env_len);
				env = getenv(key);
				if (env)
				{
					printf("env = %s\n", env);
					len += ft_strlen(env);
				}
				free(key);
				i += env_len + 1;
			}
		}
	}
	return (len);
}

// char	*expand_string(char *s, t_env *env, int exit_code);
// {
// 	size_t	i;
// 	size_t	len;
// 	char	*buf;
	
// 	len = expanded_len(s, env, exit_code);
// 	buf = malloc(len + 1);
// 	i = 0;
// 	while ()
// 	{
		
// 	}
// 	buf[i] = '\0';
// 	return (buf);
// }

// char	*expand_segment(t_segment *seg, t_env *env, int exit_code)
// {
// 	if (seg->quote_context == 1)
// 		return ;
// 	while (seg->value)
// 	{
// 		if (*(seg->value) == '$')
// 			expand_string(seg->value, env, exit_code);
// 	}
// }
