#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell);
int		main_exec(t_shell *shell);

/* one_command */
pid_t	only_cmd(t_shell *shell);
void	is_redir(t_shell *shell, t_redir *redirs);
void	close_files(t_shell *shell);

/* several_commands */
pid_t	process(t_shell *shell, int i);
int		several_cmds(t_shell *shell);
int		make_pipes(t_shell *shell, int i);

/* path */
char	*check_path(char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(char **tab, char **cmd);

/* redirection */
int		redirection_check(t_shell *shell, t_exec *exec);
int		redirect_setup(t_shell *shell);
int		if_infile(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_outfile(t_shell *shell, t_exec *exec, t_redir *redir);
int		if_no_redirection(t_exec *exec);

/* exec_utils */
int		setup_old_pipe(t_exec *exec, int idx, int old_pipe);
int		wait_process(t_shell *shell, int n);
int		count_cmd(t_cmd *cmd);
void	clear_pipe(t_shell *shell, int i);

/* exec_utils2 */
int 	exec_builtin(t_shell *shell);
bool	is_builtin(t_shell *shell);
void	count_fds(t_shell *shell);

/* here_doc */
void	handle_here_doc(t_shell *shell);

#endif