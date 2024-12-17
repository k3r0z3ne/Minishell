/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:35:41 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:53 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../includes/builtins.h"

char	*ft_getenv(const char *name, char **envp)
{
	size_t	len;
	size_t	i;

	if (!envp || !*envp || !*name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}


int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}
