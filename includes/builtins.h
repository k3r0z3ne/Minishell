#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
#include "exec.h"

/* cd */
int		ft_cd(t_shell *shell, char *path);

/* cd_utils */
void	go_prev_dir(char **envp);
void	update_pwd(t_shell *shell);


/* echo */
void	apply_flag(int flag);
int		check_flag(char **flag, int *idx);
int		ft_echo(int nb, char **arg, char **envp);

/* env */
int		ft_env(char **envp);

/* exit */
void	ft_exit(char **cmd, int status);

/* export */
int		ft_export(t_shell *shell);

/* export_utils */
void	sort_array(char **array);
void	ft_env_export(char **envp);
char	**ft_realloc_array(char **old_envp, int new_size);
int		is_valid_var(char *str);

/* pwd */
int		ft_pwd(int argc);

/* unset */
int		ft_unset(t_shell *shell);

#endif
