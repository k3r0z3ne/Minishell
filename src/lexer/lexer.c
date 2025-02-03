/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2025/02/03 16:47:00 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void check_special_cases(char *line, t_lexer *lexer)
{
	if (((line[0] == '\'' && line[1] == '\'')
			|| (line[0] == '"' && line[1] == '"')) && line[2] == '\0')
	{
		ft_putstr_fd("lexer: : command not found\n", 2);
		lexer->error = 1;
	}
	else if ((line[0] == ':' || line[0] == '!') && line[1] == '\0')
		lexer->error = 1;
	else if (line[0] == '/')
	{
		ft_putstr_fd("lexer: ", 2);
		write(2, line, ft_strlen(line));
		ft_putstr_fd(": Is a directory\n", 2);
		lexer->error = 1;
	}
}

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
	check_special_cases(line, &lexer);
	check_illegal(line, &lexer);
	lexer.expand_input = add_spaces(shell, &lexer, line);
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
