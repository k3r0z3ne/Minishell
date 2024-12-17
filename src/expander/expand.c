/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/17 15:57:52 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// inputs : "$VAR" / $VAR / "$?" / $?

void	expand_str(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*path;

	if(!token->value)
		return ;
	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	j = i + 1;
	// if (token->value[j] == '?')
	// {
	// 	case_return(token);
	// 	return ;
	// }
	while (token->value[i] && ft_isspace(token->value[i]))
		i++;
	path = ft_getenv(&token->value[i] + j, shell->envp);
	if (path == NULL)
	{
		free_token(token);
		return ;
	}
	free(token->value);
	token->value = ft_strdup(path);
}

void	expand_env(t_shell *shell, t_token *token)
{
	char	*path;

	path = NULL;
	if (!token->value)
		return ;
	// else if (token->value[1] == '?')
	// {
	// 	case_return(token);
	// 	return ;
	// }
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
