/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:37:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/28 16:20:03 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_tilde(char *path, char **envp)
{
	char	*home;
	char	*expanded_path;

	home = ft_getenv("HOME", envp);
	if (!home)
	{
		err_message2("cd", home, "HOME not set");
		return (1);
	}
	else if (home && path[1] == '\0')
	{
		if (chdir(home) != 0)
			err_message2("cd", path, NULL);
	}
	else
	{
		expanded_path = ft_strjoin2(home, &path[1]);
		if (chdir(expanded_path) != 0)
			err_message2("cd", path, NULL);
		free(expanded_path);
	}
	return (0);
}

static int	relative_path(char *path, char **envp)
{
	char	*tmp;
	char	*go_path;
	char	*pwd;

	go_path = NULL;
	pwd = ft_getenv("PWD", envp);
	if (!pwd)
		return (go_home(envp));
	tmp = ft_strjoin2(pwd, "/");
	if (!tmp)
		return (1);
	go_path = ft_strjoin2(tmp, path);
	if (!go_path)
		return (1);
	free(tmp);
	if (chdir(go_path) != 0)
	{
		free(go_path);
		err_message2("cd", path, NULL);
		return (1);
	}
	free(go_path);
	return (0);
}

int	go_home(char **envp)
{
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
	{
		err_message2("cd", home, "HOME not set");
		return (1);
	}
	if (home[0] == '\0')
		return (0);
	if (chdir(home) != 0)
	{
		err_message2("cd", home, NULL);
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *shell, char *path)
{
	int	ret;

	ret = 0;
	if (count_line(shell->cmd->full_cmd) > 2)
		return (err_message2("cd", NULL, "too many arguments"), 1);
	if (!path)
		ret = go_home(shell->envp);
	else if (path[0] == '/')
	{
		if (chdir(path) != 0)
		{
			err_message2("cd", path, NULL);
			ret = 1;
		}
	}
	else if (path[0] == '~')
		ret = expand_tilde(path, shell->envp);
	else if (path[0] == '-')
		ret = go_prev_dir(shell->envp);
	else
		ret = relative_path(path, shell->envp);
	update_pwd(shell);
	return (ret);
}
