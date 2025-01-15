/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:21 by witong            #+#    #+#             */
/*   Updated: 2025/01/15 14:33:15 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_double_ops(char *line, t_shell *shell, t_lexer *state)
{
	char *value;
	t_type type;

	type = check_double_ops(line, state->j);
	if (type != UNKNOWN)
	{
		value = ft_substr_track(shell, line, state->j, 2);
		if(!value)
			return ;
		token_add_back(&state->tokens, create_token(shell, type, value));
		state->j += 2;
	}
}

void	handle_redirection(char *line, t_shell *shell, t_lexer *state)
{
	char *value;
	t_type type;

	type = check_redirection(line[state->j]);
	value = ft_substr_track(shell, line, state->j, 1);
	if(!value)
		return ;
	token_add_back(&state->tokens, create_token(shell, type, value));
	state->j++;
}

static char	*handle_delimiter(t_lexer *state, char *value, t_type *type)
{
	t_token	*prev;

	*type = WORD;
	prev = state->tokens;
	while (prev && prev->next)
		prev = prev->next;
	if (prev && prev->type == HEREDOC)
	{
		if (state->quote == '\'')
			*type = SINGLEQ;
		else if (state->quote == '\"')
			*type = DOUBLEQ;
	}
	return (value);
}

void	handle_word(char *line, t_shell *shell, t_lexer *state)
{
	char	*value;
	t_type	type;

	state->quote = 0;  // Reset quote state
	value = extract_word(line, shell, state);
	if (!value)
		return ;
	value = handle_delimiter(state, value, &type);
	token_add_back(&state->tokens, create_token(shell, type, value));
}


