/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:16:49 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/03 17:08:26 by arotondo         ###   ########.fr       */
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
	free(tab);
	return (path);
}

char	*find_path(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp || shell->envp[0] == NULL || ft_strlen(shell->envp[0]) == 0)
		return ("");
	while (ft_strnstr(shell->envp[i], "PATH=", 5) == NULL)
		i++;
	if (shell->envp[i] == NULL || shell->envp[i][0] == '\0')
		return (NULL);
	return (shell->envp[i]);
}

char	*set_path(t_shell *shell, char **tab, char **cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	shell->cmd->cmd_len = ft_strlen(shell->cmd->full_cmd[0]);
	while (tab[i])
	{
		tmp = ft_strjoin_track(shell, tab[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin_track(shell, tmp, cmd[0]);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		path = "";
		i++;
	}
	if (if_symbolik(shell) == NULL)
		return (path);
	else
		return (if_symbolik(shell));
}

char	*if_symbolik(t_shell *shell)
{
	char	*cwd;
	char	*full_path;

	cwd = ft_strjoin_track(shell, getcwd(NULL, 0), "/");
	full_path = ft_strjoin_track(shell, cwd, shell->cmd->full_cmd[0]);
	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);
	else
		return (NULL);
}
