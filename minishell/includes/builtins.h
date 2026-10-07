/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:39:17 by ls-phabm          #+#    #+#             */
/*   Updated: 2026/06/20 20:40:03 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/************************************
 * BUILTINS
 *************************************/

int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		count_env(t_env *env);
void	sort_env_array(t_env **arr, int n);
void	fill_env_array(t_env **arr, t_env *env);
int		is_valid_identifier(char *arg);
int		is_invalid_option(char *arg);
int		option_error(char *name, char *arg);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_shell *shell, t_cmd *cmd);
int		builtin_pwd(t_shell *shell);
void	cd_free(char *path, int should_free);

#endif