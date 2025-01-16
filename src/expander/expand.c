/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:00:24 by witong            #+#    #+#             */
/*   Updated: 2025/01/16 15:12:29 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// A FAIRE PENDANT L'EXEC
// static void	case_return(t_shell *shell)
// {

// }

static int	get_var_len(char *value)
{
	int	i;

	i = 0;
	if (ft_isdigit(value[0]))
	{
		while (value[i] && ft_isdigit(value[i]))
			i++;
	}
	else
	{
		while (value[i] && (ft_isalnum(value[i]) || value[i] == '_' || value[i] == '?'))
			i++;
	}
	return (i);
}

static int	process_expand(t_shell *shell, char **result, char *value)
{
	int		len;
	char	*str;
	char	*path;

	len = get_var_len(value);
	str = ft_substr_track(shell, value, 0, len);
	if (!str)
		return (0);
	if (ft_isdigit(value[0]))
		path = ft_strdup_track(shell, "");
	else
		path = ft_getenv(str, shell->envp);
	if (!path)
		path = ft_strdup_track(shell, "");
	*result = ft_strjoin_track(shell, *result, path);
	return (len);
}

static void	handle_dollar(t_shell *shell, char *line, int *i, char **result)
{
	char	*tmp;

	if (!line[*i + 1] || (!ft_isalnum(line[*i + 1]) &&
		line[*i + 1] != '_' && line[*i + 1] != '?'))
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
	*i += process_expand(shell, result, &line[*i]);
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

void	expand_lexer(t_shell *shell, t_lexer *state, char *line)
{
	if (!shell || !state || !line)
		return;
	if (line[state->i] == '$')
	{
		if (state->is_heredoc == true || state->quote == '\'')
		{
			append_char(shell, state, line[state->i]);
			return;
		}
		handle_dollar(shell, line, &state->i, &state->expand_input);
	}
	else
		append_char(shell, state, line[state->i]);
}
