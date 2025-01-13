/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:19:22 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 12:16:09 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_empty_quotes(char *str)
{
	return (!str || !str[0] || !ft_strcmp(str, "\"\"") || !ft_strcmp(str, "\'\'"));
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '$' || c == '\'' || c == '\"');
}

int	check_double_redir(char *input, int i)
{
	return ((input[i] == '<' && input[i + 1] == '<') ||
		(input[i] == '>' && input[i + 1] == '>'));
}

void	init_state(t_lexer *state)
{
	state->i = 0;
	state->error = 0;
	state->quote = '\0';
	state->is_heredoc = 0;
	state->tokens = NULL;
}
