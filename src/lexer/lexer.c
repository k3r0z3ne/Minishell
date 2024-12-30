/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2024/12/30 14:47:44 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void process_token(char *line, t_lexer_state *state)
{
	if (ft_isspace(line[state->i]))
		state->i++;
	else if (line[state->i + 1] && is_illegal_double(line[state->i], line[state->i + 1]))
		handle_illegal_double(line[state->i], line[state->i + 1], state);
	else if (is_illegal_single(line[state->i]))
		handle_illegal_single(line[state->i], state);
	else if (check_double_ops(line, state->i) != UNKNOWN)
		handle_double_ops(line, state);
	else if (is_redirection(line[state->i]))
		handle_redirection(line, state);
	else if (line[state->i] == '\'' || line[state->i] == '\"')
		handle_quotes(line, state);
	else if (line[state->i] == '$')
		handle_dollar(line, state);
	else
		handle_word(line, state);
}

t_token *lexer(char *line)
{
	t_lexer_state state;

	state.i = 0;
	state.error = 0;
	state.tokens = NULL;
	while (line[state.i])
	{
		process_token(line, &state);
		if (state.error)
			break;
	}
	if (state.error || !state.tokens)
		return (NULL);
	token_add_back(&state.tokens, create_token(END, NULL));
	return (state.tokens);
}
