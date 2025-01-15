#ifndef PARSER_H
# define PARSER_H

typedef struct s_shell t_shell;
typedef struct s_cmd t_cmd;
typedef struct s_redir t_redir;

#include "minishell.h"

/* parser */
void	parser(t_shell *shell);

/* parser_init */
char **malloc_full_cmd(t_shell *shell, int size);
t_redir *malloc_redirs(int size);
t_cmd	*init_cmd(t_shell *shell, t_token *tokens);

/* parser_redirs */
t_redir	*create_redir(t_shell *shell, t_token *tokens);
void	redir_add_back(t_redir **redirs, t_redir *new_redir);
void	print_redirs(t_cmd *cmd);
void	print_table(t_cmd *cmd);

/* parser_utils */
int		is_word(t_type type);
int		is_redirection2(t_type type);
int		token_len(t_token *tokens);
void 	unexpected_token(t_token **tokens);
bool	validate_command(t_shell *shell);

/* parser_error */
bool	parser_error(t_token **tokens);

#endif
