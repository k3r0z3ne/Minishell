/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2025/02/28 13:09:08 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static void	check_special_cases(char *line, t_shell *shell, t_lexer *lexer)
{
	if (((line[0] == '\'' && line[1] == '\'')
			|| (line[0] == '"' && line[1] == '"')) && line[2] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->last_status = 127;
		lexer->error = 1;
	}
	else if (line[0] == ':' && line[1] == '\0')
	{
		shell->last_status = 0;
		lexer->error = 1;
	}
	else if (line[0] == '!' && line[1] == '\0')
	{
		shell->last_status = 1;
		lexer->error = 1;
	}
	else if (line[0] == '/' && is_directory(line))
	{
		err_message2(line, NULL, "Is a directory");
		shell->last_status = 126;
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

t_token	*lexer(char *line, t_shell *shell)
{
	t_lexer	lexer;

	if (!line || !*line)
		return (NULL);
	init_lexer(&lexer);
	check_illegal(line, shell, &lexer);
	lexer.expand_input = add_spaces(shell, &lexer, line);
	check_special_cases(lexer.expand_input, shell, &lexer);
	lexer.j = 0;
	while (lexer.expand_input[lexer.j])
	{
		process_token(lexer.expand_input, shell, &lexer);
		if (lexer.error)
			break ;
	}
	if (lexer.error || !lexer.tokens)
		return (NULL);
	token_add_back(&lexer.tokens, create_token(shell, END, NULL));
	return (lexer.tokens);
}
