/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2025/01/09 13:38:58 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_illegal(char *line, t_lexer_state *state)
{
	while (line[state->i])
	{
		if (line[state->i + 1] && is_illegal_double(line[state->i], line[state->i + 1]))
		{
			handle_illegal_double(line[state->i], line[state->i + 1], state);
			break ;
		}
		else if (is_illegal_single(line[state->i]))
		{
			handle_illegal_single(line[state->i], state);
			break ;
		}
		state->i++;
	}
	state->i = 0;
}

static void	process_token(char *line, t_shell *shell, t_lexer_state *state)
{
	if (ft_isspace(line[state->i]))
		state->i++;
	else if (check_double_ops(line, state->i) != UNKNOWN)
		handle_double_ops(line, shell, state);
	else if (is_redirection(line[state->i]))
		handle_redirection(line, shell, state);
	else if (line[state->i] == '\'' || line[state->i] == '\"')
		handle_quotes(line, shell, state);
	else if (line[state->i] == '$')
		handle_dollar(line, shell, state);
	else
		handle_word(line, shell, state);
}

t_token *lexer(char *line, t_shell *shell)
{
	t_lexer_state state;

	if (!line)
		return (NULL);
	state.tokens = NULL;
	state.error = 0;
	state.i = 0;
	check_illegal(line, &state);
	while (line[state.i])
	{
		process_token(line, shell, &state);
		if (state.error)
			break;
	}
	if (state.error || !state.tokens)
	{
		// free_lst_token(&state.tokens);
		return (NULL);
	}
	token_add_back(&state.tokens, create_token(shell, END, NULL));
	return (state.tokens);
}
