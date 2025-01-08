#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
#include "exec.h"

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
void	ft_exit(char **cmd, int status);

/* export */

/* pwd */
int		ft_pwd(int argc);

/* unset */

#endif