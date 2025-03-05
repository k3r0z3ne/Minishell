/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:16:49 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 13:12:11 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*check_path(t_shell *shell, char **cmd, char *env)
{
	char	*path;
	char	**tab;

	tab = NULL;
	if (env != NULL)
		tab = ft_split(env + 5, ':');
	else
		tab = ft_split(",", '/');
	if (!tab)
		return (NULL);
	path = NULL;
	path = set_path(shell, tab, cmd);
	free_array(tab);
	return (path);
}

char	*find_path(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp || shell->envp[0] == NULL || \
	ft_strlen(shell->envp[0]) == 0)
		return ("");
	while (shell->envp[i] && ft_strnstr(shell->envp[i], "PATH=", 5) == NULL)
		i++;
	if (shell->envp[i] == NULL || shell->envp[i][0] == '\0')
	{
		if (access(shell->cmd->full_cmd[0], F_OK | X_OK) == 0)
			return (shell->cmd->full_cmd[0]);
		else
			return (NULL);
	}
	else if (i == count_line(shell->envp))
		return (NULL);
	return (shell->envp[i]);
}

char	*access_check(t_shell *shell, char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (path);
		else
		{
			shell->last_status = 126;
			err_message(shell, path, NULL, NULL);
		}
	}
	return (NULL);
}

char	*set_path(t_shell *shell, char **tab, char **cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	shell->cmd->cmd_len = ft_strlen(shell->cmd->full_cmd[0]);
	path = access_check(shell, shell->cmd->full_cmd[0]);
	if (path)
		return (path);
	while (tab[i])
	{
		tmp = ft_strjoin_track(shell, tab[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin_track(shell, tmp, cmd[0]);
		if (!path)
			return (NULL);
		path = access_check(shell, path);
		if (path)
			break ;
		path = "";
		i++;
	}
	return (path);
}
