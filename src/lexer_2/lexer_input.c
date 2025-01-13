/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:24:26 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 14:46:05 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_chars(t_shell *shell, t_lexer *state, char *line, char **output)
{
	char	*tmp;

	if (line[state->i] == '\'' || line[state->i] == '\"')
	{
		if (state->quote == '\0')
			state->quote = line[state->i];
		else if (line[state->i] == state->quote)
			state->quote = '\0';
	}
	tmp = ft_substr_track(shell, line, state->i, 1);
	*output = ft_strjoin_track(shell, *output, tmp);
	state->i++;
}

static void	handle_operator_spacing(t_shell *shell, char *line,
	t_lexer *state, char **output)
{
	if (state->i > 0 && !ft_isspace(line[state->i - 1]))
		*output = ft_strjoin_track(shell, *output, " ");
	append_chars(shell, state, line, output);
	if (line[state->i] && !ft_isspace(line[state->i]))
		*output = ft_strjoin_track(shell, *output, " ");
}

static void	handle_double_operator(t_shell *shell, char *line,
	t_lexer *state, char **output)
{
	if (state->i > 0 && !ft_isspace(line[state->i - 1]))
		*output = ft_strjoin_track(shell, *output, " ");
	if (line[state->i] == '<')
		state->is_heredoc = 1;
	append_chars(shell, state, line, output);
	append_chars(shell, state, line, output);
	state->is_heredoc = 0;
	if (line[state->i] && !ft_isspace(line[state->i]))
		*output = ft_strjoin_track(shell, *output, " ");
}

int	pre_split_input(t_shell *shell, char *line, t_lexer *state,
				char **output)
{
	while (line[state->i])
	{
		if ((line[state->i] == '<' && line[state->i + 1] == '<') ||
			(line[state->i] == '>' && line[state->i + 1] == '>'))
			handle_double_operator(shell, line, state, output);
		else if (line[state->i] == '$' && !state->is_heredoc && state->quote != '\'')
			expand_lexer(shell, state, line);
		else if (line[state->i] == '<' || line[state->i] == '>' ||
				line[state->i] == '|')
			handle_operator_spacing(shell, line, state, output);
		else
			append_chars(shell, state, line, output);
	}
	if (state->quote != '\0')
	{
		ft_putstr_fd("lexer: unclosed quotes\n", 2);
		return (0);
	}
	return (1);
}

char	*process_input(t_shell *shell, char *line, t_lexer *state)
{
	char	*output;

	output = ft_strdup_track(shell, "");
	if (!output || !line)
		return (NULL);
	state->i = 0;
	if (!pre_split_input(shell, line, state, &output))
		return (NULL);
	if (is_empty_quotes(output))
	{
		ft_putstr_fd("lexer: : command not found\n", 2);
		return (NULL);
	}
	return (output);
}

void	atotokens(t_shell *shell, t_lexer *state, char *input)
{
	char	*word;

	while (input && input[state->i])
	{
		while (input[state->i] && ft_isspace(input[state->i]))
			state->i++;
		if (!input[state->i])
			break;
		word = extract_word(shell, input, state);
		if (!word || state->error)
			return ;
		if (word[0] == '\0')
		{
			free(word);
			continue;
		}
		if (!handle_token(shell, word, &shell->token))
			return ;
	}
}
