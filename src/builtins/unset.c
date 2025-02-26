/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:43:06 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/26 13:09:44 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	create_new_env(t_shell *shell, char **new_env, char *word, int wlen)
{
	int		i;
	int		j;
	bool	unset;

	i = 0;
	j = 0;
	unset = false;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], word, wlen))
			unset = true;
		else
			new_env[j++] = ft_strdup(shell->envp[i]);
		i++;
	}
	new_env[j] = NULL;
	return (unset);
}

static void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

static bool	unset_word(t_shell *shell, char *word, int wlen)
{
	char	**new_env;
	bool	unset;
	int		env_len;

	env_len = count_line(shell->envp);
	new_env = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (!new_env)
		return (false);
	unset = create_new_env(shell, new_env, word, wlen);
	if (unset)
	{
		free_env_array(shell->envp);
		shell->envp = new_env;
	}
	else
		free_env_array(new_env);
	return (unset);
}

int	ft_unset(t_shell *shell)
{
	int		i;
	int		j;
	bool	unset;

	if (!shell || !shell->envp || !shell->cmd || !shell->cmd->full_cmd)
		return (1);
	i = 1;
	j = 0;
	unset = false;
	while (shell->cmd->full_cmd[i])
	{
		j = ft_strlen(shell->cmd->full_cmd[i]);
		unset = unset_word(shell, shell->cmd->full_cmd[i], j);
		i++;
	}
	if (!unset)
		return (0);
	return (0);
}
