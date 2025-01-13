/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:02:33 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 15:01:44 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_state(t_lexer *state)
{
	char expand_input[20480];

	state->tokens = NULL;
	state->expand_input = expand_input;
	state->i = 0;
	state->j = 0;
	state->error = 0;
	state->is_heredoc = 0;
	state->quote = '\0';
}

t_type	check_redirection(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIRIN);
	else if (c == '>')
		return (REDIROUT);
	return (UNKNOWN);
}

t_type	check_double_ops(char *line, int i)
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

void	handle_illegal_single(char c, t_lexer *state)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	state->error = 1;
	state->i++;
}

void	handle_illegal_double(char c1, char c2, t_lexer *state)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c1, 2);
	ft_putchar_fd(c2, 2);
	ft_putstr_fd("'\n", 2);
	state->error = 1;
	state->i += 2;
}
