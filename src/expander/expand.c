/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/19 12:49:21 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env(t_shell *shell, t_token *token)
{
	char	*path;

	path = NULL;
	if (!token->value)
		return ;
	if (token->value[0] == '?')
	{
		printf("$?");
		// case_return(token);
		return ;
	}
	path = ft_getenv(token->value, shell->envp);
	if (path == NULL)
	{
		free_token(token);
		return ;
	}
	free(token->value);
	token->value = ft_strdup(path);
	token->type = WORD;
}

void	expander(t_shell *shell, t_token *token)
{
	if (token->type == DOUBLEQ)
		expand_str(shell, token);
	else if (token->type == DOLLAR)
		expand_env(shell, token);
}
