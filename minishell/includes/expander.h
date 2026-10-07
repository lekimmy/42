/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/20 19:43:07 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/************************************
 * STRUCT
 *************************************/

typedef struct s_exp
{
	char	*buf;
	size_t	i;
	size_t	j;
}	t_exp;

/************************************
 * FUNCTIONS
 *************************************/

size_t	var_len(char *s);
size_t	expanded_len(char *s, t_env *envs, int exit_code);

void	copy_exit_code(t_exp *exp, int exit_code);
void	copy_key_value(t_exp *exp, char *key, size_t key_len);
void	copy_literal_value(t_exp *exp);
void	copy_env_or_key_value(t_exp *exp, char *s, size_t key_len,
			t_env *envs);

void	expand_segment(t_segment *seg, t_env *envs, int exit_code);

char	*expand_string(char *s, t_env *envs, int exit_code);
char	*env_get(t_env *env, char *key);

t_env	*get_env_from_envp(char **envp);

#endif