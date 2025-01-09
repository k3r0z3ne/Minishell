/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:14:49 by witong            #+#    #+#             */
/*   Updated: 2025/01/09 13:11:04 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
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

char	**arraydup(char **array)
{
	char	**dup;
	int		lc;

	lc = count_line(array);
	dup = (char **)malloc(sizeof(char *) * (lc + 1));
	if (!dup)
		return (NULL);
	dup[lc] = NULL;
	lc = 0;
	while (array[lc])
	{
		dup[lc] = ft_strdup(array[lc]);
		if (!dup[lc])
		{
			free_array(dup);
			return (NULL);
		}
		lc++;
	}
	return (dup);
}
