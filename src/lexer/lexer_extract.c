/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:15:54 by witong            #+#    #+#             */
/*   Updated: 2025/01/15 12:05:18 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *line, t_shell *shell, t_lexer *state)
{
	int		start;

	start = state->j;
	while (line[state->j] && !ft_isspace(line[state->j])
		&& !is_redirection(line[state->j]))
	{
		if (line[state->j] == '$' && line[state->j + 1] &&
			(line[state->j + 1] == '\'' || line[state->j + 1] == '\"'))
			state->j++;
		if (line[state->j] == '\'' || line[state->j] == '"')
		{
			if (!state->quote)
				state->quote = line[state->j];
			if (!extract_quote(line, shell, state))
				return (NULL);
		}
		else
			state->j++;
	}
	return (ft_substr_track(shell, line, start, state->j - start));
}

char	*extract_quote(char *line, t_shell *shell, t_lexer *state)
{
	int		start;
	char	quote;

	quote = line[state->j];
	state->j++;
	start = state->j;
	if ((line[state->j] == '\'' || line[state->j] == '\"') && !state->tokens)
	{
		ft_putstr_fd("lexer: command not found\n", 2);
		state->error = 1;
		return (NULL);
	}
	while (line[state->j] && line[state->j] != quote)
		state->j++;
	if (!line[state->j] || line[state->j] != quote)
	{
		if (start == 1)
			ft_putstr_fd("lexer: command not found\n", 2);
		else
			ft_putstr_fd("lexer: unclosed quotes\n", 2);
		state->error = 1;
		return (NULL);
	}
	state->j++;
	return (ft_substr_track(shell, line, start, state->j - start - 1));
}

// char	*extract_dollar(char *line, t_shell *shell, t_lexer *state)
// {
// 	int		start;

// 	state->j++;
// 	start = state->j;
// 	if (!line[state->j] || ft_isspace(line[state->j]))
// 		return (ft_strdup_track(shell, "$"));
// 	while (line[state->j] && (ft_isalnum(line[state->j])
// 			|| line[state->j] == '_' || line[state->j] == '?'))
// 		state->j++;
// 	return (ft_substr_track(shell, line, start, state->j - start));
// }
