/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:04 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 16:43:01 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

/* cd */
int		ft_cd(const char *path, char **envp);

/* echo */
void	apply_flag(int flag);
int		check_flag(char **flag, int *idx);
int		ft_echo(int nb, char **arg, char **envp);

/* env */
char	*ft_getenv(const char *name, char **envp);
int		ft_env(char **envp);

/* exit */
void	ft_exit(int status);

/* export */

/* pwd */
void	ft_pwd(int argc);

/* unset */

#endif