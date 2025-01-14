/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:15:54 by witong            #+#    #+#             */
/*   Updated: 2025/01/14 15:28:42 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *line, t_shell *shell, t_lexer *state)
{
	int	start;
	char *ret;
	char *tmp;

	start = state->j;
	ret = ft_strdup_track(shell, "");
	while (line[state->j] && !ft_isspace(line[state->j]) && !is_redirection(line[(state->j)]))
	{
		if (line[state->j] == '\'' || line[state->j] == '"')
		{
			tmp = extract_quote(line, shell, state);
			if (!tmp)
				return (NULL);
			ret = ft_strjoin_track(shell, ret, tmp);
		}
		state->j++;
	}
	ret = ft_substr_track(shell, line, start, state->j - start);
	return (ret);
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
		state->j++;
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
		return (NULL);
	}
	state->j++;
	return (ft_substr_track(shell, line, start, state->j - start - 1));
}

char	*extract_dollar(char *line, t_shell *shell, t_lexer *state)
{
	int		start;

	state->j++;
	start = state->j;
	if (!line[state->j] || ft_isspace(line[state->j]))
		return (ft_strdup_track(shell, "$"));
	while (line[state->j] && (ft_isalnum(line[state->j])
			|| line[state->j] == '_' || line[state->j] == '?'))
		state->j++;
	return (ft_substr_track(shell, line, start, state->j - start));
}
