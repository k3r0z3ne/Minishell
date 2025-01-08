/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:43:06 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/08 18:39:39 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char **malloc_new_env(t_shell *shell)
{
	int env_len;
	char **new_env;

	env_len = count_line(shell->envp);
	new_env = (char **)malloc(sizeof(char *) * env_len);
	if (!new_env)
		return (NULL);
	return (new_env);
}

bool	create_new_env(t_shell *shell, char **new_env, char *word, int wlen)
{
	int		i;
	int		j;
	bool	unset;

	i = 0;
	j = 0;
	unset = false;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], word, wlen)
				&& shell->envp[i][wlen + 1] == '=')
		{
			free(shell->envp[i]);
			unset = true;
		}
		else
		{
			new_env[j] = shell->envp[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (unset);
}

bool	unset_word(t_shell *shell, char *word, int wlen)
{
	char	**new_env;
	bool	unset;

	new_env = malloc_new_env(shell);
	unset = false;
	unset = create_new_env(shell, new_env, word, wlen);
	if(shell->envp)
		free(shell->envp);
	shell->envp = new_env;
	return (unset);
}

int	ft_unset(t_shell *shell)
{
	int	i;
	int	j;
	bool unset;

	if (!shell->envp || !shell->cmd || !shell->cmd->full_cmd)
		return (1);
	i = 1;
	j = 0;
	unset = false;
	while(shell->cmd->full_cmd[i])
	{
		j = ft_strlen(shell->cmd->full_cmd[i]);
		unset = unset_word(shell, shell->cmd->full_cmd[i], j);
		printf("unset variable %d\n", i);
		i++;
	}
	if (unset)
		return (0);
	else
		return (1);
}
