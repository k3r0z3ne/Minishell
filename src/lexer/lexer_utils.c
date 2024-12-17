/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:15 by witong            #+#    #+#             */
/*   Updated: 2024/12/17 12:05:36 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_tok_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	if (value)
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
		{
			free(new_token);
			return (NULL);
		}
	}
	else
		new_token->value = NULL;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	token_add_back(t_token **list, t_token *new_token)
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
	new_token->prev = tmp;
}


void	print_tokens(t_token *head)
{
	t_token *current;

	current = head;
	while (current)
	{
		printf("[%d:%s] -> ", current->type, current->value);
		current = current->next;
	}
	printf("\n");
}

void	free_token(t_token *token)
{
	if (token)
	{
		free(token->value);
		free(token);
		token = NULL;
	}
}

void	free_lst_token(t_token **list)
{
	t_token *tmp;

	if (!list || !(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

