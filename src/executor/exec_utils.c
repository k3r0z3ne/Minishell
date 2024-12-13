/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 14:53:30 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (1);
	else
		return (0);
}

int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	return (0);
}

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
