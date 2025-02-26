/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:00:24 by witong            #+#    #+#             */
/*   Updated: 2025/02/26 18:05:09 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_string(t_shell *shell, char *line)
{
	char	*result;
	int		i;

	if (!line)
		return (NULL);
	result = ft_strdup_track(shell, "");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			handle_dollar(shell, line, &i, &result);
		else
		{
			result = ft_strjoin_track(shell, result,
					ft_substr_track(shell, line, i, 1));
			i++;
		}
	}
	free(line);
	return (result);
}

void	expand_lexer(t_shell *shell, t_lexer *state, char *line)
{
	if (!shell || !state || !line)
		return ;
	if (line[state->i] == '$')
	{
		if (state->is_heredoc == true || state->quote == '\'')
		{
			append_char(shell, state, line[state->i]);
			return ;
		}
		handle_dollar(shell, line, &state->i, &state->expand_input);
	}
	else
		append_char(shell, state, line[state->i]);
}

char	*expand_heredoc(t_shell *shell, char *line)
{
	char	*result;

	if (!line)
		return (NULL);
	result = expand_string(shell, line);
	if (!result)
		return (NULL);
	return (result);
}
