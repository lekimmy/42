/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/30 19:45:10 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/************************************
 * STRUCT
 *************************************/

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	t_word			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_word			*argv;
	t_word			*infile;
	t_word			*outfile;
	int				append;
	t_heredoc		*heredocs;
	struct s_cmd	*next;
	t_redir			*redirs;
}	t_cmd;

/************************************
 * FUNCTIONS
 *************************************/

int			is_pipe(t_token *t);
int			is_redir(t_token *t);
int			is_word(t_token *t);
int			is_full_space(char *s);

int			validate_syntax(t_token *head);
int			validate_pipe(t_token *head);
int			validate_redirection(t_token *head);
int			parse_argv(t_cmd **head, t_token *t);
int			syntax_error_at(t_token *tok);

void		set_infile(t_token *current, t_cmd *cmd);
void		set_outfile(t_token *current, t_cmd *cmd);
void		set_append(t_token *current, t_cmd *cmd);
void		set_heredoc_eof(t_token *current, t_cmd *cmd);
void		heredoc_add_back(t_heredoc **head, t_heredoc *new);

char		*op_token_str(t_token *t);

t_heredoc	*new_heredoc(t_token *current);

#endif