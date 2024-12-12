/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/12 18:18:39 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// input : "$HOME"

void	expand_str(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*path;
	t_token	*new;

	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	j = i;
	while (token->value[i] != ' ' && token->value[i] != '\t')
		i++;
	path = ft_getenv(token->value + i - j, shell->envp);
	if (path != NULL)
	{
		new = create_token(0, path);
		join_token(shell->lst, token);
	}
	free_token(token);
}

void	expand_env(t_shell *shell, t_token *token)
{
	t_token	*new;
	char	*path;

	new = NULL;
	path = NULL;
	if (!token->value || token->value[0] != '$')
		return ;
	path = ft_getenv(token->value, shell->envp);
	if (path != NULL)
	{
		new = create_token(0, path);
		join_token(shell->lst, token);
	}
	free_token(token);
}

void	expander(t_shell *shell, t_token *token)
{
	int	i;

	i = 0;
	if (token->type == 3)
		expand_str(shell, token);
	else if (token->type == 4)
		expand_env(shell, token);
}
