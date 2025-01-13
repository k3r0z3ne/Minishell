/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:41:28 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 12:07:47 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_quoted_content(t_shell *shell, char *input, t_lexer *state)
{
	char	*content;
	char	*segment;
	char	quote;
	int		start;

	quote = input[state->i];
	state->i++;
	if (state->quote == '\0')
	{
		start = state->i;
		while (input[state->i] && input[state->i] != quote)
			state->i++;
		if (!input[state->i])
		{
			state->error = 1;
			ft_putstr_fd("lexer: unclosed quotes\n", 2);
			return (NULL);
		}
		content = ft_substr_track(shell, input, start, state->i - start);
		state->i++;
		return (content);
	}
	content = NULL;
	while (input[state->i] && input[state->i] != state->quote)
	{
		segment = get_segment(shell, input, state);
		if (!segment || state->error)
			return (NULL);
		content = join_segments(shell, content, segment);
		if (!content)
			return (NULL);
	}
	return (content);
}
