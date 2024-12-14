/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 14:26:15 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// inputs : "$VAR" / $VAR / "$?" / $?

void	expand_str(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*path;
	t_token	*new;

	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	j = i + 1;
	if (token->value[j] == '?')
	{
		case_return(token);
		return ;
	}
	while (token->value[i] != ' ' && token->value[i] != '\t')
		i++;
	path = ft_getenv(token->value + i - j, shell->envp);
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
	t_token	*new;
	char	*path;

	new = NULL;
	path = NULL;
	if (!token->value || token->value[0] != '$')
		return ;
	else if (token->value[1] == '?')
	{
		case_return(token);
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
	if (token->type == 3)
		expand_str(shell, token);
	else if (token->type == 4)
		expand_env(shell, token);
}
