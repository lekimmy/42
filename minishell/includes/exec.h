/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/24 17:05:34 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <sys/stat.h>

# ifndef SAFE_FD
#  define SAFE_FD 10
# endif

/************************************
 * EXEC
 *************************************/

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	int				has_value;
	struct s_env	*next;
}	t_env;

typedef struct s_stdio
{
	int	stdin_fd;
	int	stdout_fd;
}	t_stdio;

typedef struct s_shell
{
	int		exit_code;
	t_env	*env;
	pid_t	*pids;
	int		interactive;
	int		in_pipeline;
	int		next_heredoc_fd;
	t_cmd	*cmd;
	char	*line;
	t_stdio	io;
}	t_shell;

typedef struct s_pipe
{
	int		(*pipes)[2];
	int		n;
	int		i;
}	t_pipe;

/************************************
 * EXEC
 *************************************/

void	exec_cmds(t_shell *shell, t_cmd *cmd);
void	exec_pipeline(t_shell *shell, t_cmd *cmd, int n);
void	exec_external(t_shell *shell, t_cmd *cmd);
void	exit_child(char *msg);
void	free_strtab(char **tab);
void	close_all_pipes(t_pipe *p);
void	setup_pipe_fds(t_pipe *p, t_cmd *cmd);
void	close_other_cmds_heredoc_fds(t_cmd *all_cmds, t_cmd *my_cmd);
void	close_unneeded_heredoc_fds(t_cmd *cmd);
void	close_inherited_heredoc_fds(t_shell *shell);
void	cleanup_heredoc_fds(t_cmd *cmd);
void	exit_clean(t_shell *shell, int code);

void	expand_cmds(t_shell *shell, t_cmd *cmd);
void	cmd_not_found(char **argv, t_shell *shell);
void	path_error_exit(char *name, char **argv, t_shell *shell);
void	set_exit_status_from_wait(t_shell *shell, int status);
void	handle_heredoc_exit(int fd, t_shell *shell, char *eof);

void	write_line(int fd, char *line);
void	write_expanded_line(int fd, char *line, t_shell *shell);
void	heredoc_warning(char *eof);
char	*read_heredoc_line(t_shell *shell);
void	read_heredoc_lines(int fd, int expand, t_shell *shell, char *eof);
int		collect_heredoc_nofork(t_shell *shell, t_heredoc *hd);

int		setup_redirections(t_cmd *cmd); //, t_shell *shell);
int		can_run_in_parent(t_cmd *cmd);
void	run_parent_builtin(t_shell *shell, t_cmd *cmd);
int		prepare_heredocs(t_shell *shell, t_cmd *cmd);
int		is_eof_line(char *line, char *eof);
int		get_last_heredoc_fd(t_cmd *cmd);
int		save_stdio(t_stdio *io);
void	restore_stdio(t_stdio *io);

char	*word_to_str(t_word *word);
t_word	*split_word(t_word *word);
void	append_words(t_word **head, t_word *new);
char	*find_in_path(char *name, char **dirs);
char	**split_path(char *path_val);
char	**build_argv(t_cmd *cmd);
char	**env_to_envp(t_env *env);
char	*join_error(char *cmd);

/************************************
 * ENV OPS
 *************************************/

int		env_set(t_env **head, char *key, char *value);
void	env_unset(t_env **head, char *key);
char	*env_entry_to_str(t_env *env);

#endif
