/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietri <mpietri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:34:17 by mpietri         #+#    #+#             */
/*   Updated: 2026/06/23 19:24:54 by mpietri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	count_env(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

void	sort_env_array(t_env **arr, int n)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		if (ft_strcmp(arr[i]->key, arr[i + 1]->key) > 0)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			if (i > 0)
				i -= 2;
		}
		i++;
	}
}

void	fill_env_array(t_env **arr, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
}

// valid bash identifier: starts with letter/_ then letters/digits/_
// validates the key part only (up to '=' if present)
int	is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
