/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:15 by witong            #+#    #+#             */
/*   Updated: 2024/12/11 12:25:28 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(t_tok_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	if (value)
		new_token->value = ft_strdup(value);
	else
		new_token->value = NULL;
	new_token->next = NULL;
	return (new_token);
}

void token_add_back(t_token **list, t_token *new_token)
{
	t_token *tmp;

	if (!list || !new_token)
		return ;
	if (!*list)
	{
		*list = new_token;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}


void print_tokens(t_token *token)
{
	t_token *current;

	current = token;
	while (current)
	{
		printf("[%d : '%s'] ->\n", current->type, current->value);
		current = current->next;
	}
}

