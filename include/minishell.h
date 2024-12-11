#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

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

typedef struct s_token
{
	t_tok_type type;
	char	*value;
	struct s_token *next;
}	t_token;

// lexer and utils
t_token	*lexer(char *line);
t_token	*create_token(t_tok_type type, char *value);
void token_add_back(t_token **list, t_token *new_token);
void print_tokens(t_token *token);
void handle_double_ops(const char *line, int *i, t_token **tokens);
void handle_redirection(const char *line, int *i, t_token **tokens);
void handle_quotes(const char *line, int *i, t_token **tokens);
void handle_dollar(const char *line, int *i, t_token **tokens);
void handle_word(const char *line, int *i, t_token **tokens);
char *extract_word(const char *line, int *i);
// char *extract_single_quote(const char *line, int *i);
// char *extract_double_quote(const char *line, int *i);
// char *extract_dollar(const char *line, int *i);
t_tok_type	check_redirection(char c);
t_tok_type	check_double_ops(const char *line, int i);
int	ft_isspace(char c);
int	is_redirection(char c);
int	is_special_char(char c);


char *ft_getenv(const char *name, char **envp);

#endif
