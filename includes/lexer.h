#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// Token type
typedef enum e_tok_type
{
	WORD,
	PIPE,
	SINGLEQ,
	DOUBLEQ,
	DOLLAR,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
	UNKNOWN,
	END,
}		t_tok_type;

// Token chained list
typedef struct s_token
{
	t_tok_type		type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer_state
{
	t_token	*tokens;
	int		i;
	int		error;
} t_lexer_state;

typedef struct s_shell t_shell;

/* lexer */
t_token	*lexer(char *line, t_shell *shell);

/* lexer_utils */
t_token	*create_token(t_shell *shell, t_tok_type type, char *value);
void	token_add_back(t_token **list, t_token *new_token);
void	print_tokens(t_token *head);
void	free_token(t_token **token);
void	free_lst_token(t_token **list);

/* lexer_utils2 */
int	ft_isspace(char c);
int	is_redirection(char c);
int	is_special_char(char c);
int	is_illegal_single(char c);
int	is_illegal_double(char c1, char c2);

/* lexer_utils3 */
t_tok_type	check_redirection(char c);
t_tok_type	check_double_ops(char *line, int i);
void handle_illegal_single(char c, t_lexer_state *state);
void handle_illegal_double(char c1, char c2, t_lexer_state *state);

/* lexer_handler */
void	handle_double_ops(char *line, t_shell *shell, t_lexer_state *state);
void	handle_redirection(char *line, t_shell *shell, t_lexer_state *state);
void	handle_quotes(char *line, t_shell *shell, t_lexer_state *state);
void	handle_dollar(char *line, t_shell *shell, t_lexer_state *state);
void	handle_word(char *line, t_shell *shell, t_lexer_state *state);

/* lexer_extract */
char	*extract_word(char *line, t_shell *shell, t_lexer_state *state);
char	*extract_quote(char *line, t_shell *shell, t_lexer_state *state);
char	*extract_dollar(char *line, t_shell *shell, t_lexer_state *state);

#endif
