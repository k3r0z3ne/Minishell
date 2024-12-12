/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/12 14:14:42 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// input : "$HOME"

void	expand_str(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	j = i;
	while (token->value[i] && ft_isupper(token->value[i]))
	{
		if ()
		i++;
	}
}

void	expand_env(t_shell *shell, t_token *token)
{
	
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
