/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:04:33 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/03 22:21:24 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec.h"

/* cd */
int		ft_cd(t_shell *shell, char *path);
int		go_home(char **envp);

/* cd_utils */
int		go_prev_dir(char **envp);
void	update_pwd(t_shell *shell);

/* echo */
bool	check_flag(char **flag, int *idx);
int		ft_echo(int nb, char **arg, char **envp);
void	last_check(int flag);

/* env */
int		ft_env(char **envp);

/* exit */
void	ft_exit(t_shell *shell, char **cmd);
void	simple_exit(t_shell *shell, int code);
void	exit_code(t_shell *shell, char **args);
void	exit_code_in_pipes(t_shell *shell, char **arg);

/* exit_utils */
int		test_max_min(char *arg);
int		is_exit_correct(t_shell *shell, char *arg, int i);
void	exit_err(t_shell *shell);
void	simple_exit2(t_shell *shell, int code);

/* export */
int		ft_export(t_shell *shell);

/* export_utils */
void	sort_array(char **array);
void	ft_env_export(char **envp);
char	**ft_realloc_array(char **old_envp, int new_size);
char	*get_var_name(t_shell *shell, char *str);
int		is_valid_var(char *str);

/* pwd */
int		ft_pwd(int argc);

/* unset */
int		ft_unset(t_shell *shell);

#endif
