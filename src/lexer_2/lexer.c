/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:23:02 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 12:02:58 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void lexer(char *line, t_shell *shell)
{
	t_lexer	state;

	if (!line || !*line)
		return ;
	init_state(&state);
	check_illegal(line, &state);
	if (state.error)
	{
		shell->token = NULL;
		return ;
	}
	shell->input = process_input(shell, line, &state);
	if (!shell->input)
		return ;
	state.i = 0;
	state.quote = '\0';
	shell->token = NULL;
	atotokens(shell, &state, shell->input);
	if (shell->token && !state.error)
		token_add_back(&shell->token, create_token(shell, END, NULL));
	return ;
}
