/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:35:09 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/29 02:27:16 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_new(char *envp)
{
	t_env	*env;
	size_t	key_len;
	char	*equal;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	equal = ft_strchr(envp, '=');
	key_len = equal - envp;
	env->key = ft_substr(envp, 0, key_len);
	env->value = ft_strdup(equal + 1);
	env->next = NULL;
	return (env);
}

static void	env_add_back(t_env **head, t_env *env)
{
	t_env	*current;

	current = *head;
	while (current->next)
		current = current->next;
	current->next = env;
}

t_env	*get_env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*env;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		env = env_new(envp[i]);
		env_add_back(&head, env);
		i++;
	}
	return (head);
}

// loop through each node to compare key
char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env->key);
		env = env->next;
	}
	return (NULL);
}