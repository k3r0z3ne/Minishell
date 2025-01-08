#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"

typedef struct s_shell t_shell;

/* expand */
void	expander(t_shell *shell);
void	expand_env(t_shell *shell);
void	expand_str(t_shell *shell);

/* expand_str */
void	process_expand_str(t_shell *shell, char **result, char *value);

#endif
