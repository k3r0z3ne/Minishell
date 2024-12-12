/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:15 by witong            #+#    #+#             */
/*   Updated: 2024/12/12 10:51:12 by witong           ###   ########.fr       */
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


void print_tokens(t_token *head)
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

void	free_token(t_token **list)
{
	t_token *tmp;

	if (!list || !(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

/*
int main(void)
{
	char *input = "echo hello | cat < file";
	t_token*	token = create_token(5, input);
	t_token*	token2 = create_token(10, "Hello, world");
	token_add_back(&token, token2);

	print_tokens(token);
	return (0);
}
*/

