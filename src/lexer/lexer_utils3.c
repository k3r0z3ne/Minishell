/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:02:33 by witong            #+#    #+#             */
/*   Updated: 2024/12/17 12:30:25 by witong           ###   ########.fr       */
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

t_tok_type	check_double_ops(const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (APPEND);
	return (UNKNOWN);
}
void	illegal_token(char c)
{
	ft_putstr_fd("lexer: unsupported token error near '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}
