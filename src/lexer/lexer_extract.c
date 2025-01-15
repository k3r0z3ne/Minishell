/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:15:54 by witong            #+#    #+#             */
/*   Updated: 2025/01/15 14:33:30 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_quote(char *line, t_shell *shell, t_lexer *state)
{
	int		start;
	char	quote;

	quote = line[state->j];
	state->j++;
	start = state->j;
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

char	*extract_word(char *line, t_shell *shell, t_lexer *state)
{
	char	*ret;
	char	*tmp;

	ret = ft_strdup_track(shell, "");
	while (line[state->j] && !ft_isspace(line[state->j])
		&& !is_redirection(line[state->j]))
	{
		if (line[state->j] == '$' && line[state->j + 1] &&
				(line[state->j + 1] == '\'' || line[state->j + 1] == '\"'))
			state->j++;
		if (line[state->j] == '\'' || line[state->j] == '"')
		{
			tmp = extract_quote(line, shell, state);
			if (!tmp)
				return (NULL);
		}
		else
		{
			tmp = ft_substr_track(shell, line, state->j, 1);
			state->j++;
		}
		ret = ft_strjoin_track(shell, ret, tmp);
	}
	return (ret);
}
