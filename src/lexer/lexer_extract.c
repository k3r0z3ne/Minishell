/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:15:54 by witong            #+#    #+#             */
/*   Updated: 2024/12/11 17:21:26 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_word(const char *line, int *i)
{
	int		start;

	start = *i;
	while (line[(*i)] && !ft_isspace(line[(*i)]) && !is_special_char(line[(*i)]))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}
// char *extract_single_quote(const char *line, int *i)
// {

// }
// char *extract_double_quote(const char *line, int *i)
// {

// }
// char *extract_dollar(const char *line, int *i);
