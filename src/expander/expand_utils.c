/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:27:31 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 14:24:42 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	join_token(t_token **lst, t_token *token)
{
	t_token	*next;
	t_token	*prev;

	next = NULL;
	prev = NULL;
	if (!token)
		return ;
	if (token->next)
		next = token->next;
	if (token->prev)
		prev = token->prev;
	else
		*lst = next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

// A FAIRE PENDANT L'EXEC

// void	case_return(t_token *token)
// {
	
// }
