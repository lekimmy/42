/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/24 17:04:34 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// for malloc **envp rebuild
static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->exported && env->has_value)
			n++;
		env = env->next;
	}
	return (n);
}

// rebuil envp from linked list if modified by shell
static char	**fill_envp(t_env *cur, char **envp)
{
	int	i;

	i = 0;
	while (cur)
	{
		if (cur->exported && cur->has_value)
		{
			envp[i] = env_entry_to_str(cur);
			if (!envp[i])
			{
				free_strtab(envp);
				return (NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}

// abstraction
char	**env_to_envp(t_env *env)
{
	char	**envp;

	envp = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!envp)
		return (NULL);
	return (fill_envp(env, envp));
}

static char	*join_path(char *dir, char *name)
{
	size_t	len;
	char	*full;

	len = ft_strlen(dir) + ft_strlen(name) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_memcpy(full, dir, ft_strlen(dir));
	full[ft_strlen(dir)] = '/';
	ft_memcpy(full + ft_strlen(dir) + 1, name, ft_strlen(name) + 1);
	return (full);
}

// does path exist when joining name + available dirs
// ft_strcmp for empty input ""
char	*find_in_path(char *name, char **dirs)
{
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full = join_path(dirs[i], name);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
