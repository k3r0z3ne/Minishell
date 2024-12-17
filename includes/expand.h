/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:50 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/17 14:17:03 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"

typedef struct s_shell t_shell;

/* expand */
void	expander(t_shell *shell, t_token *token);
void	expand_env(t_shell *shell, t_token *token);
void	expand_str(t_shell *shell, t_token *token);

/* expand_utils */
void	join_token(t_token **lst, t_token *token);

#endif
