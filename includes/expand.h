/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:50 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 16:18:33 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"

/* expand */
void	expander(t_shell *shell, t_token *token);
void	expand_env(t_shell *shell, t_token *token);
void	expand_str(t_shell *shell, t_token *token);

/* expand_utils */
void	join_token(t_token **lst, t_token *token);

#endif