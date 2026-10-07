/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:09:14 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/15 16:42:24 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	print_export(t_env *env)
{
	t_env	**arr;
	int		n;
	int		i;

	n = count_env(env);
	arr = malloc(sizeof(t_env *) * n);
	if (!arr)
		return ;
	fill_env_array(arr, env);
	sort_env_array(arr, n);
	i = 0;
	while (i < n)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(arr[i]->key, STDOUT_FILENO);
		if (arr[i]->has_value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(arr[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free(arr);
}

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

static int	export_one(t_shell *shell, char *arg)
{
	char	*equal;
	char	*key;
	int		ret;

	if (is_invalid_option(arg))
		return (option_error("export", arg));
	if (!is_valid_identifier(arg))
		return (export_error(arg));
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		key = ft_strdup(arg);
		ret = env_set(&shell->env, key, NULL);
	}
	else
	{
		key = ft_substr(arg, 0, equal - arg);
		if (!key)
			return (1);
		ret = env_set(&shell->env, key, equal + 1);
	}
	free(key);
	return (ret);
}

// |= > bitwise OR assignment.
// ret = ret | export_one(shell, arg);
// reports at least 1 export fail
// without it, overwriting previous errors
int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	t_word	*word;
	char	*arg;
	int		ret;

	if (!cmd->argv->next)
	{
		print_export(shell->env);
		return (0);
	}
	ret = 0;
	word = cmd->argv->next;
	while (word)
	{
		arg = word_to_str(word);
		if (arg)
			ret |= export_one(shell, arg);
		free(arg);
		word = word->next;
	}
	return (ret);
}
