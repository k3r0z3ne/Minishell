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
}	t_tok_type;

// Token chained list
typedef struct s_token
{
	t_tok_type type;
	char	*value;
	struct s_token *next;
}	t_token;

// Redirection struct
typedef struct s_redir
{
	t_tok_type	type;
	char	*file;
	struct s_redir *next;
}	t_redir;

// Command chained list
typedef struct s_cmd
{
	char	**full_path;
	struct s_redir	*redirs;
	struct s_cmd	*next;
}	t_cmd;

// lexer and utils
t_token	*lexer(char *line);
t_token	*create_token(t_tok_type type, char *value);
void	token_add_back(t_token **list, t_token *new_token);
void	free_token(t_token **list);
void	print_tokens(t_token *head);
void	handle_double_ops(const char *line, int *i, t_token **tokens);
void	handle_redirection(const char *line, int *i, t_token **tokens);
void	handle_quotes(const char *line, int *i, t_token **tokens);
void	handle_dollar(const char *line, int *i, t_token **tokens);
void	handle_word(const char *line, int *i, t_token **tokens);
char	*extract_word(const char *line, int *i);
char	*extract_single_quote(const char *line, int *i, t_token **tokens);
char	*extract_double_quote(const char *line, int *i, t_token **tokens);
char	*extract_dollar(const char *line, int *i);
t_tok_type	check_redirection(char c);
t_tok_type	check_double_ops(const char *line, int i);
int		ft_isspace(char c);
int		is_redirection(char c);
int		is_special_char(char c);


char *ft_getenv(const char *name, char **envp);

#endif
