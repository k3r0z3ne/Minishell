/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2025/01/14 14:41:22 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_token(char *line, t_shell *shell, t_lexer *state)
{
	if (ft_isspace(line[state->j]))
		state->j++;
	else if (check_double_ops(line, state->j) != UNKNOWN)
		handle_double_ops(line, shell, state);
	else if (is_redirection(line[state->j]))
		handle_redirection(line, shell, state);
	// else if (line[state->j] == '\'' || line[state->j] == '\"')
	// 	handle_quotes(line, shell, state);
	// else if (line[state->j] == '$')
	// 	handle_dollar_lexer(line, shell, state);
	else
		handle_word(line, shell, state);
}

t_token *lexer(char *line, t_shell *shell)
{
	t_lexer state;

	if (!line || !*line)
		return (NULL);
	init_state(&state);
	check_illegal(line, &state);
	add_spaces(shell, &state, line);
	printf("add_spaces: %s\n", state.expand_input);
	state.j = 0;
	while (state.expand_input[state.j])
	{
		process_token(state.expand_input, shell, &state);
		if (state.error)
			break;
	}
	if (state.error || !state.tokens)
		return (NULL);
	token_add_back(&state.tokens, create_token(shell, END, NULL));
	return (state.tokens);
}
