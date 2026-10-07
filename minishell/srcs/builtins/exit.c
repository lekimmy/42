/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:10:23 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/23 22:24:51 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	is_numeric_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol_exit(char *s)
{
	int		sign;
	long	n;

	sign = 1;
	n = 0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	return (sign * n);
}

void	exit_clean(t_shell *shell, int code)
{
	if (shell->io.stdin_fd >= 0)
		close(shell->io.stdin_fd);
	if (shell->io.stdout_fd >= 0)
		close(shell->io.stdout_fd);
	free_cmds(&shell->cmd);
	free_shell(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(code);
}

// affiche "exit", valide l'argument : non numerique -> code 2
// trop d'arguments -> erreur, code 1 sans sortir
static void	exit_not_numeric(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free(arg);
	exit_clean(shell, 2);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	char	*arg;
	int		code;

	if (shell->interactive && !shell->in_pipeline)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->argv->next)
		exit_clean(shell, shell->exit_code);
	arg = word_to_str(cmd->argv->next);
	if (!arg)
		exit_clean(shell, shell->exit_code);
	if (arg && !is_numeric_arg(arg))
		exit_not_numeric(shell, arg);
	if (cmd->argv->next->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		free(arg);
		return (1);
	}
	code = (int)(ft_atol_exit(arg) % 256 + 256) % 256;
	free(arg);
	exit_clean(shell, code);
	return (0);
}
