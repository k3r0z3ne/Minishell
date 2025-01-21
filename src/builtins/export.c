/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:25:23 by witong            #+#    #+#             */
/*   Updated: 2025/01/21 15:37:09 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
static char	**ft_realloc_array(char **old_envp, int new_size)
{
	char	**new_envp;
	int		old_len;
	int		i;

	if (!old_envp)
		return (ft_calloc(new_size, sizeof(char *)));
	new_envp = malloc(sizeof(char *) * (new_size + 1));
	if (!new_envp)
		return (NULL);
	old_len = 0;
	while (old_envp[old_len])
		old_len++;
	i = 0;
	while (i < new_size && i < old_len)
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	while (i <= new_size)
		new_envp[i++] = NULL;
	free(old_envp);
	return (new_envp);
}

static int	add_to_env(t_shell *shell, int i)
{
	int env_size;
	char	**new_env;

	env_size = 0;
	while (shell->envp && shell->envp[env_size])
		env_size++;
	new_env = ft_realloc_array(shell->envp, env_size + 1);
	if (!new_env)
		return (1);
	new_env[env_size] = ft_strdup(shell->cmd->full_cmd[i]);
	shell->envp = new_env;
	return (0);
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
