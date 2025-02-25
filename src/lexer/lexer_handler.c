/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:21 by witong            #+#    #+#             */
/*   Updated: 2025/02/22 01:16:12 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_double_ops(char *line, t_shell *shell, t_lexer *lexer)
{
	char	*value;
	t_type	type;

	type = check_double_ops(line, lexer->j);
	if (type != UNKNOWN)
	{
		value = ft_substr_track(shell, line, lexer->j, 2);
		if (!value)
			return ;
		token_add_back(&lexer->tokens, create_token(shell, type, value));
		lexer->j += 2;
	}
}

void	handle_redirection(char *line, t_shell *shell, t_lexer *lexer)
{
	char	*value;
	t_type	type;

	type = check_redirection(line[lexer->j]);
	value = ft_substr_track(shell, line, lexer->j, 1);
	if (!value)
		return ;
	token_add_back(&lexer->tokens, create_token(shell, type, value));
	lexer->j++;
}

static char	*handle_delimiter(t_lexer *lexer, char *value, t_type *type)
{
	t_token	*prev;

	*type = WORD;
	prev = lexer->tokens;
	while (prev && prev->next)
		prev = prev->next;
	if (prev && prev->type == HEREDOC)
	{
		if (lexer->quote == '\'')
			*type = SINGLEQ;
		else if (lexer->quote == '\"')
			*type = DOUBLEQ;
	}
	return (value);
}

void	handle_word(char *line, t_shell *shell, t_lexer *lexer)
{
	char	*value;
	t_type	type;

	lexer->quote = 0;
	value = extract_word(line, shell, lexer);
	if (!value)
		return ;
	value = handle_delimiter(lexer, value, &type);
	token_add_back(&lexer->tokens, create_token(shell, type, value));
}
