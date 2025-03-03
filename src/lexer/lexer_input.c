/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:27 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 14:36:12 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_char(t_shell *shell, t_lexer *lexer, char c)
{
	char	tmp[2];

	if (c == '\'' || c == '"')
	{
		if (lexer->quote == '\0')
			lexer->quote = c;
		else if (c == lexer->quote)
			lexer->quote = '\0';
	}
	tmp[0] = c;
	tmp[1] = '\0';
	lexer->expand_input = ft_strjoin_track(shell, lexer->expand_input, tmp);
	lexer->j++;
}

static void	handle_double_ops_space(t_shell *shell, t_lexer *lexer, char *line)
{
	if (lexer->i > 0 && lexer->j > 0 && !ft_isspace(line[lexer->i - 1])
		&& !ft_isspace(lexer->expand_input[lexer->j - 1]))
		append_char(shell, lexer, ' ');
	if (line[lexer->i] == '<' && line[lexer->i + 1] == '<')
		lexer->is_heredoc = true;
	append_char(shell, lexer, line[lexer->i]);
	append_char(shell, lexer, line[lexer->i]);
	if (line[lexer->i + 2] && !ft_isspace(line[lexer->i + 2]))
		append_char(shell, lexer, ' ');
	lexer->i += 2;
}

static void	handle_single_ops_space(t_shell *shell, t_lexer *lexer, char *line)
{
	if (lexer->i > 0 && lexer->j > 0 && !ft_isspace(line[lexer->i - 1])
		&& !ft_isspace(lexer->expand_input[lexer->j - 1]))
		append_char(shell, lexer, ' ');
	append_char(shell, lexer, line[lexer->i]);
	if (line[lexer->i + 1] && !ft_isspace(line[lexer->i + 1]))
		append_char(shell, lexer, ' ');
	lexer->i++;
}

char	*add_spaces(t_shell *shell, t_lexer *lexer, char *line)
{
	lexer->expand_input = ft_strdup_track(shell, "");
	while (line[lexer->i])
	{
		if (lexer->j >= 3 && ft_isspace(lexer->expand_input[lexer->j -1]) \
			&& lexer->expand_input[lexer->j - 2] != '<' \
			&& lexer->expand_input[lexer->j - 3] != '<')
			lexer->is_heredoc = false;
		if ((line[lexer->i] == '<' && line[lexer->i + 1] == '<') \
			|| (line[lexer->i] == '>' && line[lexer->i + 1] == '>'))
			handle_double_ops_space(shell, lexer, line);
		else if (line[lexer->i] == '|' || line[lexer->i] == '<' \
			|| line[lexer->i] == '>')
			handle_single_ops_space(shell, lexer, line);
		else
		{
			if (line[lexer->i] == '$' && !lexer->is_heredoc \
				&& lexer->quote != '\'')
				expand_lexer(shell, lexer, line);
			else
				append_char(shell, lexer, line[lexer->i++]);
		}
	}
	return (lexer->expand_input);
}
