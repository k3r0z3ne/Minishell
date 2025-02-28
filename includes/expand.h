/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:59:22 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/26 18:05:18 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

/* expand.c */
void	expand_lexer(t_shell *shell, t_lexer *state, char *line);
char	*expand_string(t_shell *shell, char *line);
char	*expand_heredoc(t_shell *shell, char *line);

/* expand_utils.c */
void	case_return(t_shell *shell, char **result);
int		get_var_len(char *value);
int		process_expand(t_shell *shell, char **result, char *value);
void	handle_dollar(t_shell *shell, char *line, int *i, char **result);

#endif
