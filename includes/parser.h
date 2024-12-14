/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:17:19 by witong            #+#    #+#             */
/*   Updated: 2024/12/14 14:40:41 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd t_cmd;

#include "minishell.h"

/* parser */
t_cmd	*init_cmd(t_token *tokens);
t_cmd	*parser(t_token *tokens);
void	parse_command(t_token **tokens, t_cmd **cmd);
void	parse_pipe(t_token **tokens, t_cmd **cmd);
void	parse_tokens(t_token **tokens, t_cmd **cmd);

/* parser_utils */
int		is_word(t_tok_type type);
int		is_redirection2(t_tok_type type);
int		token_len(t_token *tokens);
void	print_table(t_cmd *cmds);
void 	unexpected_token(t_token **tokens);

/* parser_redir */

/* parser_error */
bool	parser_error(t_token **tokens);

#endif