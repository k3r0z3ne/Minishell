/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:00:09 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/25 12:02:05 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef struct s_exec	t_exec;
typedef struct s_redir	t_redir;

/* parser */
void	parser(t_shell *shell);

/* parser_init */
char	**malloc_full_cmd(t_shell *shell, int size);
int		how_much_cmd(t_shell *shell);
t_exec	*init_exec(t_shell *shell);
t_cmd	*init_cmd(t_shell *shell, t_token *tokens);

/* parser_redirs */
t_redir	*create_redir(t_shell *shell, t_token *tokens);
void	redir_add_back(t_redir **redirs, t_redir *new_redir);
void	end_redir(t_shell *shell);
void	print_redirs(t_cmd *cmd);
void	print_table(t_cmd *cmd);

/* parser_utils */
int		is_word(t_type type);
int		token_len(t_token *tokens);
void	unexpected_token(t_shell *shell, t_token **tokens);

/* parser_error */
int		is_redirection3(t_type type);
int		is_redirection2(t_type type);
bool	parser_error(t_token **tokens);
bool	validate_command(t_shell *shell);

#endif
