/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 04:11:05 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/28 22:48:28 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_exit_code(t_exp *exp, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	ft_memcpy(&exp->buf[exp->j], tmp, ft_strlen(tmp));
	exp->j += ft_strlen(tmp);
	free(tmp);
	exp->i += 2;
}

void	copy_env_value(t_exp *exp, char *env)
{
	size_t	env_len;

	env_len = ft_strlen(env);
	ft_memcpy(&exp->buf[exp->j], env, env_len);
	exp->j += env_len;
}

void	copy_key_value(t_exp *exp, char *key, size_t key_len)
{
	exp->buf[exp->j++] = '$';
	ft_memcpy(&exp->buf[exp->j], key, key_len);
	exp->j += key_len;
}

void	copy_literal_value(t_exp *exp)
{
	exp->buf[(exp->j)++] = '$';
	exp->i++;
}

void	copy_env_or_key_value(t_exp *exp, char *s, size_t key_len)
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
