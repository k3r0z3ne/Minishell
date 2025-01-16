#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

/* expand.c */
void	expand_lexer(t_shell *shell, t_lexer *state, char *line);
char	*expand_string(t_shell *shell, char *line);

#endif
