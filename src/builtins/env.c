/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:35:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/03 16:01:06 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **envp)
{
	int	i;

	if (!envp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}
