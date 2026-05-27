/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:16:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/27 02:12:41 by ls-phabm         ###   ########.fr       */
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
	while (s[len] && (ft_isalpha(s[len]) || ft_isdigit(s[len]) || s[len] == '_'))
		len++;
	return (len);
}

static size_t	expanded_len(char *s, int exit_code)
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
					len += ft_strlen(env);
				else
					len += env_len;
				free(key);
				i += env_len + 1;
			}
		}
	}
	return (len);
}

// malloc len + '\0' + $
static char	*expand_string(char *s, int exit_code)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	env_len;
	size_t	key_len;
	char	*buf;
	char	*tmp;
	char	*key;
	char	*env;
	
	len = expanded_len(s, exit_code);
	printf("expanded len = %ld\n", len);
	buf = malloc(len + 2);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '$')
			buf[j++] = s[i++];
		else if (s[i + 1] == '?')
		{ // copy_exit_code()
			tmp = ft_itoa(exit_code);
			ft_memcpy(&buf[j], tmp, ft_strlen(tmp));
			j += ft_strlen(tmp);
			free(tmp);
			i += 2;
		}
		else
		{// copy env value
			key_len = var_len(&s[i + 1]);
			if (!key_len)
			{
				buf[j++] = '$';
				ft_memcpy(&buf[j], key, key_len);
				i++;
			}
			else
			{
				key = ft_substr(s, i + 1, key_len);
				env = getenv(key);
				if (env)
				{
					env_len = ft_strlen(env);
					ft_memcpy(&buf[j], env, env_len);
					j += env_len;
				}
				else
				{
					buf[j++] = '$';
					ft_memcpy(&buf[j], key, key_len);
					j += key_len;
				}
				free(key);
				i += key_len + 1;
			}
		}
	}
	buf[j] = '\0';
	// printf("expanded string: %s\n", buf);
	return (buf);
}

void	expand_segment(t_segment *seg, int exit_code)
{
	// char	*expand;
	
	if (seg->quote_context == 1)
		return ;
	seg->value = expand_string(seg->value, exit_code);
	// free(seg->value);
	// seg->value = expand;
}
