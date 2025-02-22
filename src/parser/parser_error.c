/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:37:11 by witong            #+#    #+#             */
/*   Updated: 2025/02/22 01:36:27 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection3(t_type type)
{
	return (type == REDIRIN || type == REDIROUT || type == APPEND);
}

int	is_redirection2(t_type type)
{
	return (type == REDIRIN || type == REDIROUT
		|| type == HEREDOC || type == APPEND);
}

bool	parser_error(t_token **tokens)
{
	if (!tokens || !(*tokens))
		return (true);
	if ((*tokens)->type == UNKNOWN)
		return (true);
	if ((*tokens)->type == PIPE && (!(*tokens)->prev || !(*tokens)->next
			|| (*tokens)->next->type == PIPE || (*tokens)->next->type == END))
		return (true);
	if ((*tokens)->type == HEREDOC && (!(*tokens)->next
			|| !(*tokens)->next->value || !is_word((*tokens)->next->type)))
		return (true);
	if (is_redirection3((*tokens)->type) && (!(*tokens)->next
			|| !(*tokens)->next->value || !(*tokens)->next->value[0]
			|| !is_word((*tokens)->next->type)))
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
