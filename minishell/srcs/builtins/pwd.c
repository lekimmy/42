/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:07:20 by mpietri           #+#    #+#             */
/*   Updated: 2026/06/20 20:41:07 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	builtin_pwd(t_shell *shell)
{
	char	buf[PATH_MAX];
	char	*logical;

	if (getcwd(buf, PATH_MAX))
		return (ft_putstr_fd(buf, STDOUT_FILENO),
			ft_putstr_fd("\n", STDOUT_FILENO), 0);
	logical = env_get(shell->env, "PWD");
	if (logical)
		return (ft_putstr_fd(logical, STDOUT_FILENO),
			ft_putstr_fd("\n", STDOUT_FILENO), 0);
	perror("pwd");
	return (1);
}
