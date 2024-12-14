/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:34:11 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 17:07:56 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
int		only_cmd(t_shell *shell, t_cmd *cmd);
int		main_exec(t_shell *shell, t_cmd *cmd);

/* exec_utils */
char	*check_path(char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(char **tab, char **cmd);
void	redirect_setup(t_shell *shell, t_cmd *cmd);
int		is_builtin(t_shell *shell, t_cmd *cmd);
int		ft_isupper(int c);

#endif