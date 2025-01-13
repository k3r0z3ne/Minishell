#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// Token type
typedef enum e_type
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
}		t_type;

// Token chained list
typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	char	*expand_input;
	int		i;
	int		j;
	int		error;
	int		is_heredoc;
	char	quote;
}	t_lexer;

typedef struct s_shell t_shell;

/* lexer */
t_token	*lexer(char *line, t_shell *shell);

/* lexer_input */
void	append_chars(t_shell *shell, t_lexer *state, char *input);
char	*add_spaces(t_shell *shell, t_lexer *state, char *input);

/* lexer_illegal.c */
int		is_illegal_single(char c);
int		is_illegal_double(char c1, char c2);
void	handle_illegal_single(char c, t_lexer *state);
void	handle_illegal_double(char c1, char c2, t_lexer *state);
void	check_illegal(char *line, t_lexer *state);

/* lexer_utils */
t_token	*create_token(t_shell *shell, t_type type, char *value);
void	token_add_back(t_token **list, t_token *new_token);
void	print_tokens(t_token *head);

/* lexer_utils2 */
int	ft_isspace(char c);
int	is_redirection(char c);
int	is_special_char(char c);


/* lexer_utils3 */
void	init_state(t_lexer *state);
t_type	check_redirection(char c);
t_type	check_double_ops(char *line, int i);

/* lexer_handler */
void	handle_double_ops(char *line, t_shell *shell, t_lexer *state);
void	handle_redirection(char *line, t_shell *shell, t_lexer *state);
void	handle_quotes(char *line, t_shell *shell, t_lexer *state);
void	handle_dollar_lexer(char *line, t_shell *shell, t_lexer *state);
void	handle_word(char *line, t_shell *shell, t_lexer *state);

/* lexer_extract */
char	*extract_word(char *line, t_shell *shell, t_lexer *state);
char	*extract_quote(char *line, t_shell *shell, t_lexer *state);
char	*extract_dollar(char *line, t_shell *shell, t_lexer *state);

#endif
