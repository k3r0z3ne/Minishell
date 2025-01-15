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

void	append_char(t_shell *shell, t_lexer *state, char c)
{
	char tmp[2];

	if (c == '\'' || c == '"')
	{
		if(state->quote == '\0')
			state->quote = c;
		else if (c == state->quote)
			state->quote = '\0';
	}
	tmp[0] = c;
	tmp[1] = '\0';
	state->expand_input = ft_strjoin_track(shell, state->expand_input, tmp);
	state->j++;
}

static void	handle_double_ops_space(t_shell *shell, t_lexer *state, char *line)
{
	if (state->j > 0 && !ft_isspace(line[state->j - 1])
			&& !ft_isspace(state->expand_input[state->j - 1]))
		append_char(shell, state, ' ');
	if (line[state->i] == '<' && line[state->i + 1] == '<')
		state->is_heredoc = true;
	append_char(shell, state, line[state->i]);
	append_char(shell, state, line[state->i]);
	if (line[state->i + 2] && !ft_isspace(line[state->i + 2]))
		append_char(shell, state, ' ');
	state->i += 2;
}

static void	handle_single_ops_space(t_shell *shell, t_lexer *state, char *line)
{
	if (state->j > 0 && !ft_isspace(line[state->j - 1])
			&& !ft_isspace(state->expand_input[state->j - 1]))
		append_char(shell, state, ' ');
	append_char(shell, state, line[state->i]);
	if (line[state->i + 1] && !ft_isspace(line[state->i + 1]))
		append_char(shell, state, ' ');
	state->i++;
}

char	*add_spaces(t_shell *shell, t_lexer *state, char *line)
{
	state->expand_input = ft_strdup_track(shell, "");
	while (line[state->i])
	{
		if (ft_isspace(line[state->i]))
			state->is_heredoc = false;
		if ((line[state->i] == '<' && line[state->i + 1] == '<')
				|| (line[state->i] == '>' && line[state->i + 1] == '>'))
			handle_double_ops_space(shell, state, line);
		else if (line[state->i] == '|' || line[state->i] == '<' || line[state->i] == '>')
			handle_single_ops_space(shell, state, line);
		else
		{
			if (line[state->i] == '$' && !state->is_heredoc && state->quote !='\'')
				expand_lexer(shell, state, line);
			else
			{
				append_char(shell, state, line[state->i]);
				state->i++;
			}
		}
	}
	return (state->expand_input);
}
