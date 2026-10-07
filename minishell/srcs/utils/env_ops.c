/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:57:32 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/22 16:46:24 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// rebuild **envp if shell has modified the env
char	*env_entry_to_str(t_env *env)
{
	size_t	klen;
	size_t	vlen;
	char	*entry;

	klen = ft_strlen(env->key);
	vlen = 0;
	if (env->value)
		vlen = ft_strlen(env->value);
	entry = malloc(klen + vlen + 2);
	if (!entry)
		return (NULL);
	ft_memcpy(entry, env->key, klen);
	entry[klen] = '=';
	if (env->value)
		ft_memcpy(entry + klen + 1, env->value, vlen + 1);
	else
		entry[klen + 1] = '\0';
	return (entry);
}

// updates an existing entry in place; returns 1 on failure, 0 on success
static int	env_update(t_env *cur, char *value)
{
	free(cur->value);
	if (!value)
	{
		cur->value = NULL;
		cur->has_value = 0;
		return (0);
	}
	cur->value = ft_strdup(value);
	if (!cur->value)
		return (1);
	cur->has_value = 1;
	return (0);
}

// builds a new entry and pushes it at the head of the list
static int	env_push(t_env **head, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), 1);
	new->value = NULL;
	new->has_value = 0;
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), 1);
		new->has_value = 1;
	}
	new->exported = 1;
	new->next = *head;
	*head = new;
	return (0);
}

// compare len + 1 to correctly detect diff e.g. USER & USERNAME
int	env_set(t_env **head, char *key, char *value)
{
	t_env	*cur;

	cur = *head;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
			return (env_update(cur, value));
		cur = cur->next;
	}
	return (env_push(head, key, value));
}

// remove middle or first node
void	env_unset(t_env **head, char *key)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
