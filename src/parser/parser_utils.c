/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:23:35 by witong            #+#    #+#             */
/*   Updated: 2025/02/22 13:21:27 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_word(t_type type)
{
	return (type == WORD || type == SINGLEQ || type == DOUBLEQ);
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

void	unexpected_token(t_shell *shell, t_token **tokens)
{
	if (!tokens || !*tokens)
	{
		ft_putstr_fd \
		("minishell: syntax error near unexpected token 'newline'\n", 2);
		shell->last_status = 2;
		return ;
	}
	else if (is_redirection2((*tokens)->type) && (!(*tokens)->next \
	|| !(*tokens)->next->value))
	{
		ft_putstr_fd \
		("minishell: syntax error near unexpected token 'newline'\n", 2);
		shell->last_status = 2;
		return ;
	}
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (is_redirection2((*tokens)->type))
		ft_putstr_fd((*tokens)->next->value, 2);
	else
		ft_putstr_fd((*tokens)->value, 2);
	ft_putstr_fd("'\n", 2);
	shell->last_status = 2;
}
