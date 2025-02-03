/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:15:54 by witong            #+#    #+#             */
/*   Updated: 2025/02/03 12:40:24 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_quote(char *line, t_shell *shell, t_lexer *lexer)
{
	int		start;
	char	quote;

	quote = line[lexer->j];
	lexer->j++;
	start = lexer->j;
	while (line[lexer->j] && line[lexer->j] != quote)
		lexer->j++;
	if (!line[lexer->j] || line[lexer->j] != quote)
	{
		if (start == 1)
			ft_putstr_fd("lexer: : command not found\n", 2);
		else
			ft_putstr_fd("lexer: unclosed quotes\n", 2);
		lexer->error = 1;
		return (NULL);
	}
	lexer->j++;
	return (ft_substr_track(shell, line, start, lexer->j - start - 1));
}

char	*extract_word(char *line, t_shell *shell, t_lexer *lexer)
{
	char	*ret;
	char	*tmp;

	ret = ft_strdup_track(shell, "");
	while (line[lexer->j] && !ft_isspace(line[lexer->j])
		&& !is_redirection(line[lexer->j]))
	{
		if (line[lexer->j] == '$' && line[lexer->j + 1] &&
				(line[lexer->j + 1] == '\'' || line[lexer->j + 1] == '\"'))
			lexer->j++;
		if (line[lexer->j] == '\'' || line[lexer->j] == '"')
		{
			tmp = extract_quote(line, shell, lexer);
			if (!tmp)
				return (NULL);
		}
		else
		{
			tmp = ft_substr_track(shell, line, lexer->j, 1);
			lexer->j++;
		}
		ret = ft_strjoin_track(shell, ret, tmp);
	}
	return (ret);
}
