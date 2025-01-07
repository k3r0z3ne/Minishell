/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:37:11 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/07 01:47:10 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parser_error(t_token **tokens)
{
	if (!tokens || !(*tokens))
		return (true);
	if ((*tokens)->type == UNKNOWN)
		return (true);
	if ((*tokens)->type == PIPE && (!(*tokens)->prev || !(*tokens)->next ||
			(*tokens)->next->type == PIPE || (*tokens)->next->type == END))
		return (true);
	if (is_redirection2((*tokens)->type) && (!(*tokens)->next
			|| !(*tokens)->next->value || !is_word((*tokens)->next->type)))
		return (true);
	return (false);
}
