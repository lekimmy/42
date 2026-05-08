/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/05/09 00:12:22 by ls-phabm         ###   ########.fr       */
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

typedef enum e_token_type
{
	TOKEN_WORD, // 0
	TOKEN_PIPE, // 1
	TOKEN_REDIRECT_IN, // 2
	TOKEN_REDIRECT_OUT, // 3
	TOKEN_REDIRECT_APPEND, // 4
	TOKEN_HEREDOC, // 5
	TOKEN_EOF, // 6
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;


/************************************
 * LIBFT
 *************************************/

int		ft_isspace(char c);

size_t	ft_strlen(char *s);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s);

void	free_all(t_token **head);

/************************************
 * LEXER
 *************************************/

int		is_separator(char c);
int		is_unsupported(char c);

char	quote_opened(char c);
size_t	handle_quoted_word(char *s, char *buf, size_t *i, size_t len);
void	tokenize(t_token **head, char *line);
void 	syntax_error(char c);

/************************************
 * PARSER
 *************************************/

#endif