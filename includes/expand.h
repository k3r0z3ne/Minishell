#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

/* expand.c */
void	expand_lexer(t_shell *shell, t_state *state, char *line, char **output);
char	*expand_string(t_shell *shell, char *line);

#endif
