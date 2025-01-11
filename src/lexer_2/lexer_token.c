/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:18:10 by witong            #+#    #+#             */
/*   Updated: 2025/01/11 14:48:39 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_shell *shell, t_type type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)tracked_malloc(shell, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
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

	if (!head)
		return ;
	current = head;
	while (current)
	{
		printf("[%d:%s] -> ", current->type, current->value);
		current = current->next;
	}
	printf("END\n");
}

t_type	get_token_type(char *str)
{
	if (!str || !*str)
		return (UNKNOWN);
	if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(str, "<", 1))
		return (REDIRIN);
	if (!ft_strncmp(str, ">", 1))
		return (REDIROUT);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	return (WORD);
}

int	handle_token(t_shell *shell, char *word, t_token **token)
{
	t_type	type;

	if (!word)
		return (0);
	type = get_token_type(word);
	token_add_back(token, create_token(shell, type, word));
	return (1);
}
