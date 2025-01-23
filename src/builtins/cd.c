/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:37:27 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/23 17:24:45 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_tilde(char *path, char **envp)
{
	char	*home;
	char	*expanded_path;

	home = ft_getenv("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return ;
	}
	else if (home && path[1] == '\0')
	{
		if (chdir(home) != 0)
			perror("cd failed");
		printf("%s\n", home);
	}
	else
	{
		expanded_path = ft_strjoin2(home, &path[1]);
		free(home);
		if (chdir(expanded_path) != 0)
			perror("cd failed");
		printf("%s\n", expanded_path);
	}
}

static void	simple_relative_path(char *path, char **envp)
{
	char	*tmp;
	char	*go_path;

	go_path = NULL;
	tmp = ft_strjoin2(ft_getenv("PWD", envp), "/");
	if (!tmp)
		return ;
	go_path = ft_strjoin2(tmp, path);
	if (!go_path)
		return ;
	free(tmp);
	printf("%s\n", go_path);
	if (chdir(go_path) != 0)
		perror("cd failed");
	free(go_path);
}

// static void	relative_path(char *path, char **envp)
// {
// 	if (ft_strncmp(path, ".", 1) == 0)
// 	if (ft_strncmp(path, "..", 2) == 0)

// }

static void	go_home(char **envp)
{
	char	*go_path;

	go_path = ft_getenv("HOME", envp);
	if (!go_path)
		return ;
	if (chdir(go_path) != 0)
		perror("cd failed");
	printf("%s\n", go_path);
}

int	ft_cd(t_shell *shell, char *path)
{
	if (!path)
		go_home(shell->envp);
	else if (path[0] == '/')
	{
		if (chdir(path) != 0)
			perror("cd failed");
	}
	else if (path[0] == '~')
		expand_tilde(path, shell->envp);
	else if (path[0] == '-')
		go_prev_dir(shell->envp);
	else
		simple_relative_path(path, shell->envp);
	update_pwd(shell);
	return (0);
}
