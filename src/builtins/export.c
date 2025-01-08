/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:25:23 by witong            #+#    #+#             */
/*   Updated: 2025/01/08 17:34:50 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	ft_env_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}

static int	add_to_env(t_shell *shell, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (shell->cmd->full_cmd[i][j])
	{
		if (shell->cmd->full_cmd[i][j] == '=')
		{
			while (shell->envp[k])
				k++;
			shell->envp[k] = ft_strdup(shell->cmd->full_cmd[i]);
			shell->envp[k + 1] = NULL;
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_export(t_shell *shell)
{
	int	i;

	i = 1;
	if (!shell->cmd->full_cmd[1])
		ft_env_export(shell->envp);
	else
	{
		while (shell->cmd->full_cmd[i])
		{
			add_to_env(shell, i);
			i++;
		}
	}
	return (0);
}
