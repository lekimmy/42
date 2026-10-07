/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietri <mpietri@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:32:46 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/03 17:32:48 by mpietri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

// bash: an arg like "-X" (dash + at least one char, not "--") is an invalid
// option, reported before identifier validation, and returns 2.
int	is_invalid_option(char *arg)
{
	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	if (arg[1] == '-' && arg[2] == '\0')
		return (0);
	return (1);
}

int	option_error(char *name, char *arg)
{
	char	opt[3];

	opt[0] = '-';
	opt[1] = arg[1];
	opt[2] = '\0';
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(opt, STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	return (2);
}
