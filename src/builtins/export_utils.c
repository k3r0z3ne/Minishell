/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:58:53 by witong            #+#    #+#             */
/*   Updated: 2025/02/21 19:24:24 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sort_array(char **array)
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

void	ft_env_export(char **envp)
{
	int		i;
	char	**tmp;

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

char	**ft_realloc_array(char **old_envp, int new_size)
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

char	*get_var_name(t_shell *shell, char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr_track(shell, str, 0, i);
	return (name);
}

int	is_valid_var(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
