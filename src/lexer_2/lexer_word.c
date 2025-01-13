/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:19:22 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 12:16:20 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(t_shell *shell, char *input, t_lexer *state)
{
	char	*word;
	char	*segment;

	word = NULL;
	while (input[state->i] && !ft_isspace(input[state->i]))
	{
		if ((input[state->i] == '<' || input[state->i] == '>' ||
			input[state->i] == '|') && !word)
			return (handle_operator(shell, input, state));
		segment = get_segment(shell, input, state);
		if (!segment || state->error || !(word = join_segments(shell, word, segment)))
			return (NULL);
	}
	return (word);
}

char	*handle_word_segment(t_shell *shell, char *input, t_lexer *state)
{
	char	*content;

	content = ft_substr_track(shell, input, state->i, 1);
	if (!content)
		return (NULL);
	state->i++;
	return (content);
}

char	*handle_operator(t_shell *shell, char *input, t_lexer *state)
{
	int		len;
	char	*tmp;

	if (check_double_redir(input, state->i))
		len = 2;
	else
		len = 1;
	tmp = ft_substr_track(shell, input, state->i, len);
	state->i += len;
	return (tmp);
}

char	*join_segments(t_shell *shell, char *word, char *segment)
{
	char *result;

	if (!word)
		return (ft_strdup_track(shell, segment));
	result = ft_strjoin_track(shell, word, segment);
	if (!result)
		return (NULL);
	return (result);
}

char	*get_segment(t_shell *shell, char *input, t_lexer *state)
{
	char	*result;

	if (input[state->i] == '\'' || input[state->i] == '\"')
		return (handle_quoted_content(shell, input, state));
	else if (input[state->i] == '$')
	{
		result = ft_strdup_track(shell, "");
		if (!result)
			return (NULL);
		expand_lexer(shell, state, input, &result);
		return (result);
	}
	else if (input[state->i] == '<' || input[state->i] == '>' ||
		input[state->i] == '|')
		return (NULL);
	return (handle_word_segment(shell, input, state));
}
