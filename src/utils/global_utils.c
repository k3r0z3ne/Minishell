/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:14:49 by witong            #+#    #+#             */
/*   Updated: 2025/02/24 16:56:33 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	if (c == '_')
		return (1);
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	count_line(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
