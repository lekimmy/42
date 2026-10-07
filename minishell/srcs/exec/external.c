/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:14:52 by mpietri           #+#    #+#             */
/*   Updated: 2026/07/24 17:03:21 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	exit_child(char *msg)
{
	perror(msg);
	exit(1);
}

void	free_strtab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

// str
static char	**fill_argv(t_word *word, char **argv)
{
	int	i;

	i = 0;
	while (word)
	{
		argv[i] = word_to_str(word);
		if (!argv[i])
			return (free_strtab(argv), NULL);
		word = word->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

// str table
char	**build_argv(t_cmd *cmd)
{
	t_word	*word;
	char	**argv;
	int		n;

	n = 0;
	word = cmd->argv;
	while (word)
	{
		n++;
		word = word->next;
	}
	argv = malloc(sizeof(char *) * (n + 1));
	if (!argv)
		return (NULL);
	return (fill_argv(cmd->argv, argv));
}

void	cmd_not_found(char **argv, t_shell *shell)
{
	char	*msg;

	if (ft_strchr(argv[0], '/'))
		path_error_exit(argv[0], argv, shell);
	msg = join_error(argv[0]);
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		free(msg);
	}
	free_all(argv, shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(127);
}
