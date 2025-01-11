/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:25:24 by witong            #+#    #+#             */
/*   Updated: 2025/01/05 06:13:30 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_redirection(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '$' || c == '\'' || c == '\"');
}

int	is_illegal_single(char c)
{
	if (c == '\\' || c == ';' || c == '(' || c == ')'
			|| c == '&' || c == '#' || c == '*' || c == '`'
			|| c == '[' || c == ']' || c == '{' || c == '}')
		return (1);
	return (0);
}

int	is_illegal_double(char c1, char c2)
{
	if ((c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') || (c1 == '$' && c2 == '$'))
		return (1);
	return (0);
}
