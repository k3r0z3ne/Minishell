/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:57:25 by witong            #+#    #+#             */
/*   Updated: 2025/02/26 13:00:41 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_prev_dir(char **envp)
{
	char	*go_path;

	go_path = ft_getenv("OLDPWD", envp);
	if (!go_path)
		return (1);
	if (chdir(go_path) != 0)
	{
		err_message2("cd", go_path, NULL);
		return (1);
	}
	printf("%s\n", go_path);
	return (0);
}

static char	*join_path_to_env(char *env_var, char *new_path)
{
	char	*tmp;
	char	*new_entry;

	tmp = ft_strjoin2(env_var, "=");
	if (!tmp)
		return (NULL);
	new_entry = ft_strjoin2(tmp, new_path);
	free(tmp);
	return (new_entry);
}

static int	find_replace_entry(t_shell *shell, char *env_var, char *new_entry)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], env_var, ft_strlen(env_var)) == 0 \
			&& shell->envp[i][ft_strlen(env_var)] == '=')
		{
			free(shell->envp[i]);
			shell->envp[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (i);
}

static void	set_env(t_shell *shell, char *env_var, char *new_path)
{
	char	*new_entry;
	char	**old_envp;
	int		i;

	if (!shell || !env_var || !new_path)
		return ;
	new_entry = join_path_to_env(env_var, new_path);
	if (!new_entry)
		return ;
	i = find_replace_entry(shell, env_var, new_entry);
	if (i > 0)
	{
		old_envp = shell->envp;
		shell->envp = ft_realloc_array(old_envp, i + 2);
		if (!shell->envp)
		{
			free(new_entry);
			shell->envp = old_envp;
			return ;
		}
		shell->envp[i] = new_entry;
		shell->envp[i + 1] = NULL;
	}
}

void	update_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	set_env(shell, "OLDPWD", ft_getenv("PWD", shell->envp));
	set_env(shell, "PWD", cwd);
	free(cwd);
}
