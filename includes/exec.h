#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell);
pid_t	process(t_shell *shell, int i);
int		several_cmds(t_shell *shell);
pid_t	only_cmd(t_shell *shell);
int		main_exec(t_shell *shell);

/* path */
char	*check_path(char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(char **tab, char **cmd);

/* redirection */
int		redirection_check(t_shell *shell, t_exec *exec, t_redir *redirs);
int		redirect_setup(t_exec *exec, t_redir *redir);
void	is_redir(t_exec *exec, t_cmd *cmd);
void	clear_pipe(t_exec *exec);

/* exec_utils */
void	parent_process(t_exec *exec, t_redir *redir);
int		setup_old_pipe(t_exec *exec, int idx, int old_pipe);
int		make_pipes(t_shell *shell, int i);
int		wait_process(t_shell *shell, int n);
int		count_cmd(t_cmd *cmd);

/* exec_utils2 */
int 	exec_builtin(t_shell *shell);
bool	is_builtin(t_shell *shell);

/* here_doc */
void	handle_here_doc(t_shell *shell);

#endif