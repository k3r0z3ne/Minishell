/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:56 by witong            #+#    #+#             */
/*   Updated: 2024/12/14 13:39:02 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *lexer(char *line)
{
	t_token *tokens;
	int 	i;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (check_double_ops(line, i) != UNKNOWN)
			handle_double_ops(line, &i, &tokens);
		else if (is_redirection(line[i]))
			handle_redirection(line, &i, &tokens);
		else if (line[i] == '\'' || line[i] == '\"')
			handle_quotes(line, &i, &tokens);
		else if (line[i] == '$')
			handle_dollar(line, &i, &tokens);
		else
			handle_word(line, &i, &tokens);
	}
	token_add_back(&tokens, create_token(END, NULL));
	return (tokens);
	return (tokens);
}
