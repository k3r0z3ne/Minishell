/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:16:49 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/16 17:17:18 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*check_path(char **cmd, char *env)
{
	char	*path;
	char	**tab;

	tab = NULL;
	if (env != NULL)
		tab = ft_split(env + 5, ':');
	else
		tab = ft_split(".", '/');
	if (!tab)
	{
		// free_array(tab);
		return (NULL);
	}
	path = NULL;
	path = set_path(tab, cmd);
	// printf("check_path path : %s\n", path);
	free(tab);
	return (path);
}

char	*find_path(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp || shell->envp[0] == NULL || ft_strlen(shell->envp[0]) == 0)
		return ("");
	// if (ft_strncmp(shell->envp[i], "LD_LIBRARY_PATH=/usr/lib/debug", 31) == 0)
	// 	return ("");
	while (ft_strnstr(shell->envp[i], "PATH=", 5) == NULL)
		i++;
	if (shell->envp[i] == NULL || shell->envp[i][0] == '\0')
		return (NULL);
	return (shell->envp[i]);
}

char	*set_path(char **tab, char **cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (tab[i])
	{
		tmp = ft_strjoin(tab[i], "/");
		if (!tmp)
			return (free(tab), NULL);
		path = ft_strjoin(tmp, cmd[0]);
		if (!path)
			return (free(tmp), NULL);
		if (access(path, F_OK) == 0)
			break ;
		free (path);
		path = "";
		i++;
	}
	// printf("set_path path : %s\n", path);
	return (path);
}
