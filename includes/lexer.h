/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:59:28 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/21 20:00:00 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// Token type
typedef enum e_type
{
	UNKNOWN,
	WORD,
	PIPE,
	SINGLEQ,
	DOUBLEQ,
	DOLLAR,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
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
	bool	error;
	bool	is_heredoc;
	char	quote;
}	t_lexer;

typedef struct s_shell	t_shell;

/* lexer */
t_token	*lexer(char *line, t_shell *shell);

/* lexer_input */
void	append_char(t_shell *shell, t_lexer *lexer, char c);
char	*add_spaces(t_shell *shell, t_lexer *lexer, char *input);

/* lexer_illegal */
void	check_illegal(char *line, t_shell *shell, t_lexer *lexer);

/* lexer_handler */
void	handle_double_ops(char *line, t_shell *shell, t_lexer *lexer);
void	handle_redirection(char *line, t_shell *shell, t_lexer *lexer);
void	handle_word(char *line, t_shell *shell, t_lexer *lexer);

/* lexer_extract */
char	*extract_word(char *line, t_shell *shell, t_lexer *lexer);

/* lexer_token */
t_token	*create_token(t_shell *shell, t_type type, char *value);
void	token_add_back(t_token **list, t_token *new_token);
void	print_tokens(t_token *head);

/* lexer_utils */
void	init_lexer(t_lexer *lexer);
int		ft_isspace(char c);
int		is_redirection(char c);
t_type	check_redirection(char c);
t_type	check_double_ops(char *line, int i);

#endif
