/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/07/04 03:10:38 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

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
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	LPAR,
	RPAR,
	SEMICOL
}	t_operator_type;

typedef enum e_quote_context
{
	NONE,
	SINGLE,
	DOUBLE
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
		t_word			*word;
		t_operator_type	operator;
	};
	struct s_token	*next;
}	t_token;

typedef struct s_heredoc
{
	t_word				*eof;
	int					expand;
	int					fd;
	struct s_heredoc	*next;

}	t_heredoc;

/************************************
 * LEXER
 *************************************/

int			is_separator(char c);
int			is_unsupported(char c);

int			tokenize(t_token **head, char *line);
void		syntax_error(char *msg, char *token);

t_token		*new_token_operator(t_operator_type operator);
t_token		*handle_operator(char *s, size_t *i);

t_segment	*handle_segments(char *s, size_t *i, t_segment *segment);

t_token		*new_token_word(t_word *word);
t_token		*handle_word(char *s, size_t *i);

t_segment	*new_segment(char *value, char quote);
void		add_segment(t_segment **segment, t_segment *new_segment);
int			handle_quoted_segment(char *s, char *buf, size_t *i, size_t *j);
void		handle_normal_segment(char *s, char *buf, size_t *i, size_t *j);

#endif