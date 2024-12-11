/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2024/12/11 14:11:43 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_tok_type	check_type(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIRIN);
	else if (c == '>')
		return (REDIROUT);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '\'')
		return (SIMPLEQ);
	else if (c == '\"')
		return (DOUBLEQ);
	return (UNKNOWN);
}

static t_tok_type	check_double_ops(const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (APPEND);
	return (UNKNOWN);
}

static char	*extract_word(const char *line, int *i)
{
	int		count;

	count = *i;
	while (line[(*i)] && !ft_isspace(line[(*i)]) && !is_special_char(line[(*i)]))
		(*i)++;
	return (ft_substr(line, count, *i - count));
}

t_token	*lexer(char *line)
{
	t_token		*tokens;
	char		*value;
	t_tok_type	type;
	int			i;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if ((type = check_double_ops(line, i)) != UNKNOWN)
		{
			value = ft_substr(line, i, 2);
			token_add_back(&tokens, create_token(type, value));
			i += 2;
		}
		else if(is_operator(line[i]))
		{
			type = check_type(line[i]);
			value = ft_substr(line, i, 1);
			token_add_back(&tokens, create_token(type, value));
			i++;
		}
		else
		{
			value = extract_word(line, &i);
			token_add_back(&tokens, create_token(WORD, value));
		}
	}
	token_add_back(&tokens, create_token(END, NULL));
	return (tokens);
}
