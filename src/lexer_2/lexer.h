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

typedef struct s_state
{
	char	*line;
	t_token	*tokens;
	int		i;
	int		error;
	char	quote;
	int		is_heredoc;
} t_state;

typedef struct s_shell t_shell;

/* lexer.c */
void	lexer(char *line, t_shell *shell);

/* lexer_input.c */
char	*process_input(t_shell *shell, char *line, t_state *state);
void	append_chars(t_shell *shell, t_state *state, char *line, char **output);
void	atotokens(t_shell *shell, t_state *state, char *input);
int		pre_split_input(t_shell *shell, char *line, t_state *state, char **output);

/* lexer_token.c */
t_token	*create_token(t_shell *shell, t_type type, char *value);
void	token_add_back(t_token **head, t_token *new_token);
void	print_tokens(t_token *head);
t_type	get_token_type(char *str);
int		handle_token(t_shell *shell, char *word, t_token **token);

/* lexer_word.c */
char	*extract_word(t_shell *shell, char *input, t_state *state);
char	*handle_word_segment(t_shell *shell, char *input, t_state *state);
char	*handle_operator(t_shell *shell, char *input, t_state *state);
char	*join_segments(t_shell *shell, char *word, char *segment);
char	*get_segment(t_shell *shell, char *input, t_state *state);

/* lexer_quote.c */
char	*handle_quoted_content(t_shell *shell, char *input, t_state *state);

/* lexer_illegal.c */
int		is_illegal_single(char c);
int		is_illegal_double(char c1, char c2);
void	handle_illegal_single(char c, t_state *state);
void	handle_illegal_double(char c1, char c2, t_state *state);
void	check_illegal(char *line, t_state *state);

/* lexer_utils.c */
int		ft_isspace(char c);
int		is_empty_quotes(char *str);
int		is_special_char(char c);
int		check_double_redir(char *input, int i);
void	init_state(t_state *state);

#endif
