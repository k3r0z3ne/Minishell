#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/* execution */
void	exec_cmd(t_shell *shell, t_cmd *cmd);
pid_t	process(t_shell *shell, t_cmd *cmd, int i, int n);
pid_t	only_cmd(t_shell *shell, t_cmd *cmd);
int		several_cmds(t_shell *shell, t_cmd *cmd);
int		main_exec(t_shell *shell, t_cmd *cmd);

/* path */
char	*check_path(char **cmd, char *env);
char	*find_path(t_shell *shell);
char	*set_path(char **tab, char **cmd);

/* redirection */
void	redirection_check(t_cmd *cmd, t_redir *redirs);
void    is_redir(t_cmd *cmd);
void    redirect_setup(t_cmd *cmd, int i, int n);

/* exec_utils */
void	parent_process(t_cmd *cmd, int i, int n);
int		wait_process(t_cmd *cmd, int n);
int		is_builtin(t_shell *shell, t_cmd *cmd);
int		count_cmd(t_cmd *cmd);

/* here_doc */
void	manage_here_doc(t_shell *shell, t_cmd *cmd);
void	handle_here_doc(t_shell *shell, t_cmd *cmd);

#endif