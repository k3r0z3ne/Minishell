/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/08 11:56:36 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A FAIRE PENDANT L'EXEC
// void	case_return(t_token *token)
// {

// }

void	expand_env(t_shell *shell)
{
	char	*path;

	if (!shell->token || !shell->token->value)
		return ;
	if (shell->token->value[0] == '?')
	{
		printf("$?");
		// case_return(token);
		return ;
	}
	path = NULL;
	path = ft_getenv(shell->token->value, shell->envp);
	if (!path)
		path = ft_strdup_track(shell, "");
	free(shell->token->value);
	shell->token->value = ft_strdup_track(shell, path);
	shell->token->type = WORD;
}

void	expander(t_shell *shell)
{
	if (shell->token->type == DOUBLEQ)
		expand_str(shell);
	else if (shell->token->type == DOLLAR)
		expand_env(shell);
}
