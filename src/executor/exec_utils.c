/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 17:07:50 by arotondo         ###   ########.fr       */
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
		free_tab(tab);
		return (NULL);
	}
	path = NULL;
	path = set_path(tab, cmd);
	free(tab);
	return (path);
}

char	*find_path(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp || shell->envp[0] == NULL || ft_strlen(shell->envp[0]) == 0)
		return ("");
	if (ft_strncmp(shell->envp[i], "LD_LIBRARY_PATH=/usr/lib/debug", 31) == 0)
		return ("");
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
	return (path);
}

void	redirect_setup(t_shell *shell, t_cmd *cmd)
{
	if (dup2(cmd->infile, STDIN_FILENO) < 0)
		return ;
	if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
		return ;
}

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
