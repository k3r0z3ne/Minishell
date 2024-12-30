/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:37:11 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/27 12:13:14 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parser_error(t_token **tokens)
{
	if (!tokens || !(*tokens))
		return (unexpected_token(tokens), true);
	else if ((*tokens)->type == UNKNOWN)
		return (unexpected_token(tokens), true);
	else if ((*tokens)->type == PIPE && ((*tokens)->next && (*tokens)->next->type == PIPE))
		return (unexpected_token(tokens), true);
	else if ((*tokens)->type == PIPE && (!(*tokens)->next || (*tokens)->next->type == END))
		return (unexpected_token(tokens), true);
	else if (!(*tokens)->prev && (*tokens)->type == PIPE)
		return (unexpected_token(tokens), true);
	else if (is_redirection2((*tokens)->type) && (!(*tokens)->next || !is_word((*tokens)->next->type)))
		return (unexpected_token(tokens), true);
	return (false);
}
