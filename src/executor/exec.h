/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:34:11 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 14:54:18 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../../include/minishell.h"

/* execution */
int		only_cmd(t_shell *shell, t_cmd *cmd);
int		main_exec(t_shell *shell, t_cmd *cmd);

/* exec_utils */
int		is_builtin(t_shell *shell, t_cmd *cmd);
int		ft_isupper(int c);
char	*ft_getenv(const char *name, char **envp);

#endif