/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:16:29 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/28 03:59:18 by ls-phabm         ###   ########.fr       */
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

static void get_expanded_len(size_t *len, char *s, size_t env_len, size_t *i)
{
	char	*key;
	char	*value;

	key = ft_substr(s, *i + 1, env_len);
	value = getenv(key);
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

static void get_exit_code_len(size_t *len, size_t *i, int exit_code)
{
	*len += ft_nbrlen(exit_code);
	*i += 2;
}

static size_t	expanded_len(char *s, int exit_code)
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
				get_expanded_len(&len, s, env_len, &i);
		}
	}
	return (len);
}

static t_exp *init_exp(char *s, int exit_code)
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

static void	copy_exit_code(t_exp *exp, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	ft_memcpy(&exp->buf[exp->j], tmp, ft_strlen(tmp));
	exp->j += ft_strlen(tmp);
	free(tmp);
	exp->i += 2;
}

static void	copy_env_value(t_exp *exp, char *env)
{
	size_t	env_len;

	env_len = ft_strlen(env);
	ft_memcpy(&exp->buf[exp->j], env, env_len);
	exp->j += env_len;
}

static void	copy_key_value(t_exp *exp, char *key, size_t key_len)
{
	exp->buf[exp->j++] = '$';
	ft_memcpy(&exp->buf[exp->j], key, key_len);
	exp->j += key_len;
}

static void copy_literal_value(t_exp *exp)
{
	exp->buf[(exp->j)++] = '$';
	exp->i++;
}

static void copy_env_or_key_value(t_exp *exp, char *s, size_t key_len)
{
	char	*key;
	char	*env;

	key = ft_substr(s, exp->i + 1, key_len);
	env = getenv(key);
	if (env)
		copy_env_value(exp, env);
	else
		copy_key_value(exp, key, key_len);
	free(key);
	exp->i += key_len + 1;
}

// malloc len + '\0' + $
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
