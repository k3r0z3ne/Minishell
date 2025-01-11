/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:00:24 by witong            #+#    #+#             */
/*   Updated: 2025/01/11 14:49:19 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_expand(t_shell *shell, char **result, char *value)
{
	int		i;
	int		start;
	char	*str;
	char	*path;

	i = 0;
	start = i;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_' || value[i] == '?'))
		i++;
	str = ft_substr_track(shell, value, start, i);
	if (!str)
		return (0);
	path = ft_getenv(str, shell->envp);
	if (!path)
		path = ft_strdup_track(shell, "");
	*result = ft_strjoin_track(shell, *result, path);
	return (i);
}

static void	handle_dollar(t_shell *shell, char *line, int *i, char **result)
{
	char	*tmp;
	int		chars_processed;

	if (!line[*i + 1] || line[*i + 1] == ' ' || line[*i + 1] == '$')
	{
		tmp = ft_substr_track(shell, line, *i, 1);
		*result = ft_strjoin_track(shell, *result, tmp);
		(*i)++;
		return ;
	}
	(*i)++;
	if (line[*i] == '?')
	{
		// case_return(shell);
		(*i)++;
		return ;
	}
	chars_processed = process_expand(shell, result, &line[*i]);
	*i += chars_processed;
	if (line[*i] == ' ')
	{
		tmp = ft_substr_track(shell, line, *i, 1);
		*result = ft_strjoin_track(shell, *result, tmp);
		(*i)++;
	}
}

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
	return (result);
}

void	expand_lexer(t_shell *shell, t_state *state, char *line, char **output)
{
	if (!shell || !state || !line || !output)
		return;
	if (line[state->i] == '$')
	{
		if (state->is_heredoc || state->quote == '\'')
		{
			append_chars(shell, state, line, output);
			return;
		}
		handle_dollar(shell, line, &state->i, output);
	}
	else
	{
		append_chars(shell, state, line, output);
	}
}
