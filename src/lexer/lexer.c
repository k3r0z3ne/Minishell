/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 16:54:45 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	process_token(char *line, t_shell *shell, t_lexer *state)
// {
// 	if (ft_isspace(line[state->i]))
// 		state->i++;
// 	else if (check_double_ops(line, state->i) != UNKNOWN)
// 		handle_double_ops(line, shell, state);
// 	else if (is_redirection(line[state->i]))
// 		handle_redirection(line, shell, state);
// 	// else if (line[state->i] == '\'' || line[state->i] == '\"')
// 	// 	handle_quotes(line, shell, state);
// 	// else if (line[state->i] == '$')
// 	// 	handle_dollar_lexer(line, shell, state);
// 	else
// 		handle_word(line, shell, state);
// }

t_token *lexer(char *line, t_shell *shell)
{
	t_lexer state;

	if (!line || !*line)
		return (NULL);
	init_state(&state);
	check_illegal(line, &state);
	printf("input: %s\n", line);
	add_spaces(shell, &state, line);
	printf("output: %s\n", state.expand_input);
	// while (line[state.i])
	// {
	// 	process_token(line, shell, &state);
	// 	if (state.error)
	// 		break;
	// }
	// if (state.error || !state.tokens)
	// 	return (NULL);
	// token_add_back(&state.tokens, create_token(shell, END, NULL));
	return (state.tokens);
}
