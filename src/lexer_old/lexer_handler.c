/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:21 by witong            #+#    #+#             */
/*   Updated: 2025/01/09 13:19:53 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_double_ops(char *line, t_shell *shell, t_lexer_state *state)
{
	char *value;
	t_tok_type type;

	type = check_double_ops(line, state->i);
	if (type != UNKNOWN)
	{
		value = ft_substr_track(shell, line, state->i, 2);
		if(!value)
			return ;
		token_add_back(&state->tokens, create_token(shell, type, value));
		state->i += 2;
		// free(value);
	}
}

void	handle_redirection(char *line, t_shell *shell, t_lexer_state *state)
{
	char *value;
	t_tok_type type;

	type = check_redirection(line[state->i]);
	value = ft_substr_track(shell, line, state->i, 1);
	if(!value)
		return ;
	token_add_back(&state->tokens, create_token(shell, type, value));
	state->i++;
	// free(value);
}

void	handle_quotes(char *line, t_shell *shell, t_lexer_state *state)
{
	char		*value;
	t_tok_type	type;

	type = SINGLEQ;
	if (line[state->i] == '\"')
		type = DOUBLEQ;
	value = extract_quote(line, shell, state);
	if (!value)
		return ;
	token_add_back(&state->tokens, create_token(shell, type, value));
	// free(value);
}

void	handle_dollar(char *line, t_shell *shell, t_lexer_state *state)
{
	char *value;
	t_tok_type	type;

	value = extract_dollar(line, shell, state);
	if (!value)
		return ;
	if (ft_strcmp(value, "$") == 0)
		type = WORD;
	else
		type = DOLLAR;
	token_add_back(&state->tokens, create_token(shell, type, value));
	// free(value);
}

void	handle_word(char *line, t_shell *shell, t_lexer_state *state)
{
	char *value;

	value = extract_word(line, shell, state);
	if(!value)
		return ;
	token_add_back(&state->tokens, create_token(shell, WORD, value));
	// free(value);
}
