/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:10 by witong            #+#    #+#             */
/*   Updated: 2024/12/10 16:21:46 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(t_tok_type type, const char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token)
}

void print_tokens(t_token *token)
{
	t_token *current;

	current = token;
	while (current)
	{
		printf(Type: %d, Value: %s\n, current->type, current->value);
		current = current->next;
	}
}
