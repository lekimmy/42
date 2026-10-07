/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:35:09 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/22 17:00:27 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env	*env)
{
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

static t_env	*env_new(char *envp)
{
	t_env	*env;
	char	*equal;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	equal = ft_strchr(envp, '=');
	if (equal)
	{
		env->key = ft_substr(envp, 0, equal - envp);
		env->value = ft_strdup(equal + 1);
		env->has_value = 1;
	}
	else
	{
		env->key = ft_strdup(envp);
		env->value = NULL;
		env->has_value = 0;
	}
	if (!env->key || (equal && !env->value))
		return (free_env_node(env), NULL);
	env->exported = 0;
	env->next = NULL;
	return (env);
}

static void	env_add_back(t_env **head, t_env *env)
{
	t_env	*current;

	if (!*head)
	{
		*head = env;
		return ;
	}
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
		if (env)
		{
			env->exported = 1;
			env->has_value = 1;
			env_add_back(&head, env);
		}
		i++;
	}
	return (head);
}

// loop through each node to compare key
char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
