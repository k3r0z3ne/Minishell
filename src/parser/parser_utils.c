/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:23:35 by witong            #+#    #+#             */
/*   Updated: 2024/12/16 14:09:25 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_word(t_tok_type type)
{
	return (type == WORD || type == SINGLEQ || type == DOUBLEQ);
}

int	is_redirection2(t_tok_type type)
{
	return (type == REDIRIN || type == REDIROUT || type == HEREDOC || type == APPEND);
}
int	token_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

void	unexpected_token(t_token **tokens)
{
	ft_putstr_fd("parser: syntax error near unexpected token '", 2);
	ft_putstr_fd((*tokens)->value, 2);
	ft_putstr_fd("'\n", 2);
}
