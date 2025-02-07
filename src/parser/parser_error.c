/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:37:11 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/06 17:36:02 by arotondo         ###   ########.fr       */
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
	// if ((*tokens)->type == HEREDOC && (!(*tokens)->next
	// 		|| !(*tokens)->next->value || !is_word((*tokens)->next->type)))
	// 	return (true);
	if (is_redirection2((*tokens)->type) && (!(*tokens)->next
			|| !(*tokens)->next->value || !(*tokens)->next->value[0] || !is_word((*tokens)->next->type)))
		return (true);
	return (false);
}
