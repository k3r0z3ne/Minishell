/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:15:54 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 12:01:26 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *line, t_shell *shell, t_lexer *state)
{
	int	start;
	char *ret;
	char *tmp;

	start = state->i;
	ret = ft_strdup_track(shell, "");
	while (line[state->i] && !ft_isspace(line[state->i]) && !is_special_char(line[(state->i)]))
	{
		if (line[state->i] == '\'' || line[state->i] == '"')
		{
			tmp = extract_quote(line, shell, state);
			if (!tmp)
				return (NULL);
			ret = ft_strjoin_track(shell, ret, tmp);
		}
		state->i++;
	}
	ret = ft_substr_track(shell, line, start, state->i - start);
	return (ret);
}

char	*extract_quote(char *line, t_shell *shell, t_lexer *state)
{
	int		start;
	char	quote;

	quote = line[state->i];
	state->i++;
	start = state->i;
	if ((line[state->i] == '\'' || line[state->i] == '\"') && !state->tokens)
	{
		ft_putstr_fd("lexer: command not found\n", 2);
		state->i++;
		return (NULL);
	}
	while (line[state->i] && line[state->i] != quote)
		state->i++;
	if (!line[state->i] || line[state->i] != quote)
	{
		if (start == 1)
			ft_putstr_fd("lexer: command not found\n", 2);
		else
			ft_putstr_fd("lexer: unclosed quotes\n", 2);
		return (NULL);
	}
	state->i++;
	return (ft_substr_track(shell, line, start, state->i - start - 1));
}

char	*extract_dollar(char *line, t_shell *shell, t_lexer *state)
{
	int		start;

	state->i++;
	start = state->i;
	if (!line[state->i] || ft_isspace(line[state->i]))
		return (ft_strdup_track(shell, "$"));
	while (line[state->i] && (ft_isalnum(line[state->i])
			|| line[state->i] == '_' || line[state->i] == '?'))
		state->i++;
	return (ft_substr_track(shell, line, start, state->i - start));
}
