/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:02:05 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/09 18:56:09 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	name_is_builtin(char *name)
{
	return (ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "exit", 5) == 0);
}

// does cmd start with builtin (first arg / word)
// abstraction
int	is_builtin(t_cmd *cmd)
{
	char	*name;
	int		res;

	if (!cmd->argv)
		return (0);
	name = word_to_str(cmd->argv);
	if (!name)
		return (0);
	res = name_is_builtin(name);
	free(name);
	return (res);
}

int	dispatch_builtin(t_shell *shell, t_cmd *cmd, char *name)
{
	if (ft_strncmp(name, "echo", 5) == 0)
		return (builtin_echo(cmd), 0);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (builtin_pwd(shell));
	if (ft_strncmp(name, "export", 7) == 0)
		return (builtin_export(shell, cmd));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (builtin_unset(shell, cmd));
	if (ft_strncmp(name, "env", 4) == 0)
		return (builtin_env(shell), 0);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (builtin_exit(shell, cmd));
	return (-1);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;
	int		ret;

	name = word_to_str(cmd->argv);
	if (!name)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
	{
		free(name);
		return (builtin_exit(shell, cmd));
	}
	ret = dispatch_builtin(shell, cmd, name);
	free(name);
	return (ret);
}
