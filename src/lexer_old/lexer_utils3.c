/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:02:33 by witong            #+#    #+#             */
/*   Updated: 2025/01/05 11:21:05 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok_type	check_redirection(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIRIN);
	else if (c == '>')
		return (REDIROUT);
	return (UNKNOWN);
}

t_tok_type	check_double_ops(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (APPEND);
	if (line[i] == '&' && line[i + 1] == '&')
		return (UNKNOWN);
	if (line[i] == '|' && line[i + 1] == '|')
		return (UNKNOWN);
	return (UNKNOWN);
}

void	handle_illegal_single(char c, t_lexer_state *state)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	state->error = 1;
	state->i++;
}

void	handle_illegal_double(char c1, char c2, t_lexer_state *state)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c1, 2);
	ft_putchar_fd(c2, 2);
	ft_putstr_fd("'\n", 2);
	state->error = 1;
	state->i += 2;
}
