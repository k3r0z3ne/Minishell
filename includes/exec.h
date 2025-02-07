#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell);
int		main_exec(t_shell *shell);

/* one_command */
pid_t	process1(t_shell *shell);
int		only_cmd(t_shell *shell);
void	is_redir(t_shell *shell, t_redir *redirs);
void	close_files(t_shell *shell);

/* several_commands */
pid_t	process(t_shell *shell);
int		several_cmds(t_shell *shell);
int		make_pipes(t_shell *shell);

/* path */
char	*check_path(t_shell *shell, char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(t_shell *shell, char **tab, char **cmd);

/* redirection */
int		redirection_check(t_shell *shell, t_exec *exec);
int		redirect_setup(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_infile(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_outfile(t_exec *exec, t_redir *redir);

/* exec_utils */
int		is_fd_open(int fd);
int		setup_old_pipe(t_exec *exec);
int		wait_process(t_shell *shell, int n);
int		count_cmd(t_cmd *cmd);

/* exec_utils2 */
void	exec_builtin(t_shell *shell);
bool	is_builtin(t_shell *shell);
void	count_fds(t_shell *shell);

/* here_doc */
char	*expand_heredoc(t_shell *shell, char *line);
void	handle_here_doc(t_shell *shell);

#endif