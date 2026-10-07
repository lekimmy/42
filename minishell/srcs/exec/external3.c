/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:13:07 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/24 17:03:55 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// for a name with '/': print a bash-like error and exit (126 or 127)
void	path_error_exit(char *name, char **argv, t_shell *shell)
{
	struct stat	st;

	ft_putstr_fd(name, STDERR_FILENO);
	if (access(name, F_OK) != 0)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_all(argv, shell);
		exit(127);
	}
	if (stat(name, &st) == 0 && S_ISDIR(st.st_mode))
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	free_all(argv, shell);
	exit(126);
}

static char	*resolve_path(char *name, t_env *env)
{
	char	*path_val;
	char	**dirs;
	char	*result;

	if (ft_strchr(name, '/'))
	{
		if (access(name, F_OK) == 0 && access(name, X_OK) == 0)
			return (ft_strdup(name));
		return (NULL);
	}
	path_val = env_get(env, "PATH");
	if (!path_val)
		path_val = "/usr/local/bin:/usr/bin:/bin";
	dirs = split_path(path_val);
	if (!dirs)
		return (NULL);
	result = find_in_path(name, dirs);
	free_strtab(dirs);
	return (result);
}

// bash stats the path first
// if S_ISDIR(st_mode) = true, reports "Is a directory"
// doesn't even attempt execve
// bash uses 126 for "found but not executable"
static void	check_is_directory(char **argv, t_shell *shell, char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free(path);
		free_all(argv, shell);
		exit(126);
	}
}

// exec external command (not builtin) if exists
// execve replaces current program
// execve failed: map errno to bash-like exit status
static void	execve_error(char *path, char **argv, char **envp)
{
	int	code;

	ft_putstr_fd(path, STDERR_FILENO);
	if (errno == ENOENT)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		code = 127;
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		code = 126;
	}
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		code = 126;
	}
	free_strtab(argv);
	free_strtab(envp);
	free(path);
	exit(code);
}

void	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	**argv;
	char	**envp;
	char	*path;

	setup_exec_signals();
	if (!cmd->argv)
	{
		free_shell(shell);
		exit(0);
	}
	argv = build_argv(cmd);
	if (!argv)
		exit_child("build_argv");
	if (!argv[0][0] || is_full_space(argv[0]))
		cmd_not_found(argv, shell);
	path = resolve_path(argv[0], shell->env);
	if (!path)
		cmd_not_found(argv, shell);
	check_is_directory(argv, shell, path);
	envp = env_to_envp(shell->env);
	if (!envp)
		return (free_strtab(argv), free(path), (void)exit_child("envp"));
	free_shell(shell);
	execve(path, argv, envp);
	execve_error(path, argv, envp);
}
