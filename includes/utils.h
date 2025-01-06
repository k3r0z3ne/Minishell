#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* clean_up */
void	free_array(char **array);
void	free_redir(t_redir **redir);
void	free_redirs(t_redir **redirs);
void	free_cmd(t_cmd **cmd);

/* global utils */
int		ft_isupper(int c);
int		count_line(char **array);
char	**arraydup(char **array);

/* init */
void	init_shell(t_shell *shell, int argc, char **argv, char **envp);

#endif
