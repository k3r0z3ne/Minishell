/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:34:11 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/17 12:35:55 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell, t_cmd *cmd);
pid_t	process(t_shell *shell, t_cmd *cmd, int i);
pid_t	only_cmd(t_shell *shell, t_cmd *cmd);
int		several_cmds(t_shell *shell, t_cmd *cmd);
int		main_exec(t_shell *shell, t_cmd *cmd);

/* path */
char	*check_path(char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(char **tab, char **cmd);

/* exec_utils */
void	prt_process(t_cmd *cmd, int i, int n);
void	redirect_setup(t_cmd *cmd, int i, int n);
int		wait_process(t_cmd *cmd, int n);
int		is_builtin(t_shell *shell, t_cmd *cmd);
int		ft_isupper(int c);

#endif