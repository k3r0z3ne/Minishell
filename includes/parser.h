/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:17:19 by witong            #+#    #+#             */
/*   Updated: 2024/12/17 11:51:05 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd t_cmd;
typedef struct s_redir t_redir;

#include "minishell.h"

/* parser */
void	parse_command(t_token **tokens, t_cmd **cmd);
void	parse_pipe(t_token **tokens, t_cmd **cmd);
void	parse_tokens(t_token **tokens, t_cmd **cmd);
t_cmd	*parser(t_token *tokens);

/* parser_init */
char **malloc_full_cmd(int size);
t_redir *malloc_redirs(int size);
t_cmd	*init_cmd(t_token *tokens);

/* parser_utils */
int		is_word(t_tok_type type);
int		is_redirection2(t_tok_type type);
int		token_len(t_token *tokens);
void 	unexpected_token(t_token **tokens);

/* parser_utils2 */
t_redir	*create_redir(t_token *tokens);
void	redir_add_back(t_redir **redirs, t_redir *new_redir);
void	print_redirs(t_cmd *cmd);
void	print_table(t_cmd *cmds);

/* parser_error */
bool	parser_error(t_token **tokens);

#endif
