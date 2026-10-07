/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:06:47 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/13 20:07:35 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	update_pwd(t_shell *shell, char *old_path, char *arg)
{
	char	buf[PATH_MAX];
	char	*old;
	size_t	len;

	if (old_path)
		env_set(&shell->env, "OLDPWD", old_path);
	if (getcwd(buf, PATH_MAX))
		return ((void)env_set(&shell->env, "PWD", buf));
	if (arg && *arg == '/')
		return ((void)env_set(&shell->env, "PWD", arg));
	old = env_get(shell->env, "PWD");
	if (!old || !arg)
		return ;
	len = ft_strlen(old);
	if (len + ft_strlen(arg) + 2 > PATH_MAX)
		return ;
	ft_memcpy(buf, old, len);
	buf[len] = '/';
	ft_memcpy(buf + len + 1, arg, ft_strlen(arg) + 1);
	env_set(&shell->env, "PWD", buf);
}

static char	*get_cd_path(t_shell *shell, t_cmd *cmd, int *should_free)
{
	char	*arg;
	char	*path;

	if (!cmd->argv->next)
	{
		path = env_get(shell->env, "HOME");
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (path);
	}
	arg = word_to_str(cmd->argv->next);
	if (!arg)
		return (NULL);
	if (ft_strncmp(arg, "-", 2) != 0)
		return (*should_free = 1, arg);
	free(arg);
	path = env_get(shell->env, "OLDPWD");
	if (!path)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (path);
}

static void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

// bash prints this when the current directory no longer exists, but still
// performs the chdir and returns 0
static void	getcwd_warning(void)
{
	ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: "
		"cannot access parent directories: No such file or directory\n",
		STDERR_FILENO);
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	old_buf[PATH_MAX];
	char	*old_path;
	int		should_free;

	should_free = 0;
	if (cmd->argv->next && cmd->argv->next->next)
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	old_path = getcwd(old_buf, PATH_MAX);
	if (!old_path)
		getcwd_warning();
	path = get_cd_path(shell, cmd, &should_free);
	if (!path)
		return (1);
	if (*path && chdir(path) == -1)
		return (cd_error(path), cd_free(path, should_free), 1);
	update_pwd(shell, old_path, path);
	cd_free(path, should_free);
	return (0);
}
