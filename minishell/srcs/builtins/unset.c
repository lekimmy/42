/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:09:36 by mpietri           #+#    #+#             */
/*   Updated: 2026/06/20 20:41:09 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

// a name with '=' or invalid chars is not a valid identifier for unset
static int	valid_unset_id(char *key)
{
	if (!key || !is_valid_identifier(key))
		return (0);
	if (ft_strchr(key, '='))
		return (0);
	return (1);
}

static int	unset_error(char *key)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	t_word	*word;
	char	*key;
	int		ret;

	ret = 0;
	word = cmd->argv->next;
	while (word)
	{
		key = word_to_str(word);
		if (key && is_invalid_option(key))
			return (option_error("unset", key), free(key), 2);
		if (key && !valid_unset_id(key))
			ret = unset_error(key);
		else if (key)
			env_unset(&shell->env, key);
		free(key);
		word = word->next;
	}
	return (ret);
}
