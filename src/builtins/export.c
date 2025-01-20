/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:25:23 by witong            #+#    #+#             */
/*   Updated: 2025/01/20 15:56:57 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	sort_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strncmp(array[i], array[j], ft_strlen(array[i])) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_env_export(char **envp)
{
	int	i;
	char **tmp;

	i = 0;

	tmp = arraydup(envp);
	sort_array(tmp);
	while (tmp[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putendl_fd(tmp[i], 1);
		i++;
	}
	free_array(tmp);
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
