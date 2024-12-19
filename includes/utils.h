#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* clean_up */
int		ft_isupper(int c);
int		count_line(char **array);
void	free_array(char **array);
char	**arraydup(char **array);

/* init */
void	init_shell(t_shell *shell, int argc, char **argv, char **envp);

#endif