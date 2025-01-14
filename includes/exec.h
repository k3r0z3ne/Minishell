#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell);
pid_t	process(t_shell *shell);
int		several_cmds(t_shell *shell);
pid_t	only_cmd(t_shell *shell);
int		main_exec(t_shell *shell);

/* path */
char	*check_path(char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(char **tab, char **cmd);

/* redirection */
int		redirection_check(t_shell *shell, t_exec *exec, t_redir *redirs);
void	is_redir(t_exec *exec, t_cmd *cmd);
int		redirect_setup(t_exec *exec);
void	clear_pipe(t_exec *exec, int count);

/* exec_utils */
void	parent_process(t_exec *exec);
int		make_pipes(t_shell *shell, int i);
int		wait_process(t_shell *shell, int n);
int		is_builtin(t_shell *shell);
int		count_cmd(t_cmd *cmd);

/* here_doc */
void	handle_here_doc(t_shell *shell);

#endif