/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:21 by witong            #+#    #+#             */
/*   Updated: 2024/12/27 18:41:13 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_double_ops(char *line, t_lexer_state *state)
{
	char *value;
	t_tok_type type;

	type = check_double_ops(line, state->i);
	if (type != UNKNOWN)
	{
		value = ft_substr(line, state->i, 2);
		if(!value)
			return ;
		token_add_back(&state->tokens, create_token(type, value));
		state->i += 2;
	}
}

void	handle_redirection(char *line, t_lexer_state *state)
{
	char *value;
	t_tok_type type;

	type = check_redirection(line[state->i]);
	value = ft_substr(line, state->i, 1);
	if(!value)
		return ;
	token_add_back(&state->tokens, create_token(type, value));
	(state->i)++;
}

void	handle_quotes(char *line, t_lexer_state *state)
{
	char *value;

	if (line[state->i] == '\'')
	{
		value = extract_single_quote(line, state);
		if (!value)
			return ;
		token_add_back(&state->tokens, create_token(SINGLEQ, value));
	}
	else if (line[state->i] == '\"')
	{
		value = extract_double_quote(line, state);
		if (!value)
			return ;
		token_add_back(&state->tokens, create_token(DOUBLEQ, value));
	}
}

void	handle_dollar(char *line, t_lexer_state *state)
{
	char *value;
	t_tok_type	type;

	value = extract_dollar(line, state);
	if (!value)
		return ;
	if (ft_strcmp(value, "$") == 0)
		type = WORD;
	else
		type = DOLLAR;
	token_add_back(&state->tokens, create_token(type, value));
}

void	handle_word(char *line, t_lexer_state *state)
{
	char *value;

	value = extract_word(line, state);
	if(!value)
		return ;
	token_add_back(&state->tokens, create_token(WORD, value));
}
