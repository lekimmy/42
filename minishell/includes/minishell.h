/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/21 08:04:52 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <sys/time.h>	// gettimeofday
# include <unistd.h>	// usleep, write
# include <stdint.h>	// SIZE_MAX
# include <readline/readline.h>
# include <readline/history.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

/************************************
 * LEXER
 *************************************/

typedef enum e_token_type
{
	WORD,
	OPERATOR
}	t_token_type;

typedef enum e_operator_type
{
	PIPE, // 0
	REDIRECT_IN, // 1
	REDIRECT_OUT, // 2
	REDIRECT_APPEND, // 3
	HEREDOC // 4
	// EOF // 5
}	t_operator_type;

typedef enum e_quote_context
{
	NONE, // 0
	SINGLE, // 1
	DOUBLE // 2
}	t_quote_context;

typedef struct s_segment
{
	int					quote_context;
	char				*value;
	struct s_segment	*next;
}	t_segment;

typedef struct s_word
{
	t_segment		*segments;
	struct s_word	*next;
}	t_word;

typedef struct s_token
{
	t_token_type	type;

	union
	{
		t_word		*word;
		t_operator_type	operator;
	};
	
	struct s_token	*next;
}	t_token;

/************************************
 * PARSER
 *************************************/

typedef struct s_cmd
{
	t_word			*argv;
	t_word			*infile;
	t_word			*outfile;
	int				append;
	t_word			*heredoc_eof;
	struct s_cmd	*next;
}	t_cmd;

/************************************
 * EXEC
 *************************************/

typedef struct s_shell
{
	int		exit_code;
	// t_env	*env;
	pid_t	*pids;
	int		interactive;
}	t_shell;

/************************************
 * LIBFT
 *************************************/

int		ft_isspace(char c);

size_t	ft_strlen(char *s);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s);

void	free_tokens(t_token **head);
void	free_segments(t_segment **head);
void	free_cmds(t_cmd **head);
void	ft_putstr_fd(char *s, int fd);

/************************************
 * LEXER
 *************************************/

int		is_separator(char c);
int		is_unsupported(char c);

int		tokenize(t_token **head, char *line);
void	lexer_error(char *msg, char *token);

t_token	*new_token_operator(t_operator_type operator);
t_token	*handle_operator(char *s, size_t *i);

t_segment	*handle_segments(char *s, size_t *i, t_segment *segment);

t_token	*new_token_word(t_word *word);
t_token *handle_word(char *s, size_t *i);

t_segment	*new_segment(char *value, char quote);
void	add_segment(t_segment **segment, t_segment *new_segment);
int		handle_quoted_segment(char *s, char *buf, size_t *i, size_t *j);
void	handle_normal_segment(char *s, char *buf, size_t *i, size_t *j);

/************************************
 * PARSER
 *************************************/
int		is_pipe(t_token *t);
int		is_redir(t_token *t);
int		is_word(t_token *t);

int		validate_syntax(t_token *head);
t_cmd	*new_command(t_token *t);
void	add_command(t_cmd **head, t_cmd *new_cmd);
int		parse_argv(t_cmd **head, t_token *t);

#endif