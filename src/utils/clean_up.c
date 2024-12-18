/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:15:56 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/18 16:55:44 by arotondo         ###   ########.fr       */
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

void	free_array(char **array)
{
	int	i;
	int	size;

	i = 0;
	size = count_line(array);
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
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
