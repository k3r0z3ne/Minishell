/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:37:11 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/21 19:54:27 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parser_error(t_token **tokens)
{
	if (!tokens || !(*tokens))
		return (true);
	if ((*tokens)->type == UNKNOWN)
		return (true);
	if ((*tokens)->type == PIPE && (!(*tokens)->prev || !(*tokens)->next || \
			(*tokens)->next->type == PIPE || (*tokens)->next->type == END))
		return (true);
	if ((*tokens)->type == HEREDOC && (!(*tokens)->next
			|| !(*tokens)->next->value || !is_word((*tokens)->next->type)))
		return (true);
	if (is_redirection3((*tokens)->type) && (!(*tokens)->next \
		|| !(*tokens)->next->value || !(*tokens)->next->value[0] || \
		!is_word((*tokens)->next->type)))
		return (true);
	return (false);
}

bool	validate_command(t_shell *shell)
{
	int	i;

	if (!shell || !shell->cmd || !shell->cmd->full_cmd)
		return (false);
	i = 0;
	while (shell->cmd->full_cmd[i])
	{
		if (!shell->cmd->full_cmd[i][0])
			return (false);
		i++;
	}
	if (i == 0)
		return (false);
	return (true);
}
