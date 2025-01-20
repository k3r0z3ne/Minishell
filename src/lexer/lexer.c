/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2025/01/20 17:42:56 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_token(char *line, t_shell *shell, t_lexer *lexer)
{
	if (ft_isspace(line[lexer->j]))
		lexer->j++;
	else if (check_double_ops(line, lexer->j) != UNKNOWN)
		handle_double_ops(line, shell, lexer);
	else if (is_redirection(line[lexer->j]))
		handle_redirection(line, shell, lexer);
	else
		handle_word(line, shell, lexer);
}

t_token *lexer(char *line, t_shell *shell)
{
	t_lexer lexer;

	if (!line || !*line)
		return (NULL);
	init_lexer(&lexer);
	check_illegal(line, &lexer);
	lexer.expand_input = add_spaces(shell, &lexer, line);
	// printf("add_spaces: %s\n", lexer.expand_input);
	lexer.j = 0;
	while (lexer.expand_input[lexer.j])
	{
		process_token(lexer.expand_input, shell, &lexer);
		if (lexer.error)
			break;
	}
	if (lexer.error || !lexer.tokens)
		return (NULL);
	token_add_back(&lexer.tokens, create_token(shell, END, NULL));
	return (lexer.tokens);
}
