/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:35 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/11 17:04:23 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	expand_str(t_shell *shell, t_token *token)
{
	t_token	*tmp;
	int		i;
	char	*replace;

	tmp = token;
	i = 0;
	replace = NULL;
	while (tmp->value[i] != '$')
		i++;
	if (tmp->value[i] == '$')
	{
		replace = ft_getenv(tmp->value + i, shell->envp);
		if (replace == NULL)
			return ;
		tmp->value = replace;
	}
	
}

void	expander(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == 3)
			expand_str(token);
		else if (token->type == 4)
			expand_env(&token);
		token = token->next;
	}
}
