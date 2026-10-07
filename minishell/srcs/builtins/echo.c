/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:05:35 by mpietri           #+#    #+#             */
/*   Updated: 2026/06/20 20:40:51 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

// n nn nnn = valid n flags
// i > 1 = reject bare - & accept i*n
// is there at least 1 n after - ?
static int	is_flag_n(t_word *word)
{
	char	*s;
	int		i;

	s = word_to_str(word);
	if (!s)
		return (0);
	if (s[0] != '-')
		return (free(s), 0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (free(s), 0);
		i++;
	}
	free(s);
	return (i > 1);
}

int	builtin_echo(t_cmd *cmd)
{
	t_word	*word;
	char	*str;
	int		newline;

	newline = 1;
	word = cmd->argv->next;
	while (word && is_flag_n(word))
	{
		newline = 0;
		word = word->next;
	}
	while (word)
	{
		str = word_to_str(word);
		if (str)
			ft_putstr_fd(str, STDOUT_FILENO);
		free(str);
		if (word->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		word = word->next;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
