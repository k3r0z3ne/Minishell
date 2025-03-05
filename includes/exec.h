/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:03:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 14:06:22 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell);
void	tty_handler(t_shell *shell);
void	only_infile(t_shell *shell);
int		main_exec(t_shell *shell);

/* one_command */
pid_t	process1(t_shell *shell);
int		only_cmd(t_shell *shell);
void	is_redir(t_shell *shell, t_redir *redirs);

/* several_commands */
void	parent_pr(t_shell *shell);
pid_t	process(t_shell *shell);
int		several_cmds(t_shell *shell);
int		make_pipes(t_shell *shell);

/* path */
char	*check_path(t_shell *shell, char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*access_check(t_shell *shell, char *path);
char	*set_path(t_shell *shell, char **tab, char **cmd);

/* redirection */
int		redirect_setup(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_infile(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_outfile(t_shell *shell, t_exec *exec, t_redir *redir);

/* redirection2 */
int		redirect_setup2(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_infile2(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_outfile2(t_shell *shell, t_exec *exec, t_redir *redir);

/* exec_utils */
int		is_fd_open(int fd);
int		setup_old_pipe(t_shell *shell, t_exec *exec);
int		wait_process(t_shell *shell, int n);
int		count_cmd(t_cmd *cmd);

/* exec_utils2 */
void	exec_builtin(t_shell *shell);
bool	is_builtin(t_shell *shell);
void	count_fds(t_shell *shell);
int		count_heredoc(t_shell *shell);

/* here_doc */
int		iter_heredoc(t_shell *shell);
void	process_heredoc(t_shell *shell);
int		loop_heredoc(t_shell *shell);
void	redir_heredoc(t_shell *shell, char *file);
int		interrupt_heredoc(t_shell *shell, char *line);

#endif
