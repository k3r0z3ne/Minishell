/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:02:33 by witong            #+#    #+#             */
/*   Updated: 2025/01/14 17:07:48 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_state(t_lexer *state)
{
	state->tokens = NULL;
	state->i = 0;
	state->j = 0;
	state->error = 0;
	state->is_heredoc = false;
	state->quote = '\0';
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_redirection(char c)
{
	return (c == '|' || c == '<' || c == '>');
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

