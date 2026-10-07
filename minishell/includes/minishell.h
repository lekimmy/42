/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/04 03:16:18 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "expander.h"
# include "signals.h"

# define PATH_MAX 4096
# define BUFFER_SIZE 10

/************************************
 * LIBFT
 *************************************/

int		ft_isspace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

size_t	ft_strlen(char *s);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char *s, char sep);
char	*get_next_line(int fd);

void	ft_putstr_fd(char *s, int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);

/************************************
 * FREE
 *************************************/

void	free_tokens(t_token **head);
void	free_segments(t_segment **head);
void	free_cmds(t_cmd **head);
void	free_token_list(t_token **head);
void	free_env(t_env **head);
void	free_strtab(char **tab);
void	free_word_list(t_word **head);
void	free_heredocs(t_heredoc **head);
void	free_redirs(t_redir **head);
void	free_shell(t_shell *shell);
void	free_all(char **argv, t_shell *shell);
void	handle_lex_parse_error(t_shell *shell, t_token **token);

int		ft_nbrlen(int n);

/************************************
 * BUILTINS
 *************************************/

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_pwd(t_shell *shell);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_shell *shell, t_cmd *cmd);

#endif
