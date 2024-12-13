/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:15:57 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 16:33:15 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_tok_type type;
	char	*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

// lexer and utils
t_token	*lexer(char *line);
t_token	*create_token(t_tok_type type, char *value);
void	token_add_back(t_token **list, t_token *new_token);
void	free_token(t_token **list);
void	print_tokens(t_token *token);
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
int		is_onlyspaces(char *str);

#endif
