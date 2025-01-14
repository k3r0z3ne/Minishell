/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:23:35 by witong            #+#    #+#             */
/*   Updated: 2025/01/14 18:28:49 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection2(t_type type)
{
	return (type == REDIRIN || type == REDIROUT || type == HEREDOC || type == APPEND);
}

int	token_len(t_token *tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->type != END)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	unexpected_token(t_token **tokens)
{
	if (!tokens || !*tokens)
	{
		ft_putstr_fd("parser: syntax error near unexpected token 'newline'\n", 2);
		return ;
	}
	else if (is_redirection2((*tokens)->type) && (!(*tokens)->next || !(*tokens)->next->value))
	{
		ft_putstr_fd("parser: syntax error near unexpected token 'newline'\n", 2);
		return ;
	}
	ft_putstr_fd("parser: syntax error near unexpected token '", 2);
	if (is_redirection2((*tokens)->type))
		ft_putstr_fd((*tokens)->next->value, 2);
	else
		ft_putstr_fd((*tokens)->value, 2);
	ft_putstr_fd("'\n", 2);
}

bool	validate_command(t_shell *shell)
{
	int	i;

	if (!shell || !shell->cmd || !shell->cmd->full_cmd)
		return (false);
	i = 0;
	while (shell->cmd->full_cmd[i])
	{
		if (!shell->cmd->full_cmd[i][0])  // Empty string check
			return (false);
		i++;
	}
	if (i == 0)  // No command provided
		return (false);
	return (true);
}
