/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:04:42 by witong            #+#    #+#             */
/*   Updated: 2025/02/22 13:07:08 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_return(t_shell *shell, char **result)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(shell->last_status);
	if (!exit_status_str)
		return ;
	*result = ft_strjoin_track(shell, *result, exit_status_str);
	free(exit_status_str);
}

int	get_var_len(char *value)
{
	int	i;

	i = 0;
	if (ft_isdigit(value[0]))
	{
		while (value[i] && ft_isdigit(value[i]))
			i++;
	}
	else
	{
		while (value[i]
			&& (ft_isalnum(value[i]) || value[i] == '_' || value[i] == '?'))
			i++;
	}
	return (i);
}

int	process_expand(t_shell *shell, char **result, char *value)
{
	int		len;
	char	*str;
	char	*path;

	len = get_var_len(value);
	str = ft_substr_track(shell, value, 0, len);
	if (!str)
		return (0);
	if (ft_isdigit(value[0]))
		path = ft_strdup_track(shell, "");
	else
		path = ft_getenv(str, shell->envp);
	if (!path)
		path = ft_strdup_track(shell, "");
	*result = ft_strjoin_track(shell, *result, path);
	return (len);
}

void	handle_dollar(t_shell *shell, char *line, int *i, char **result)
{
	char	*tmp;

	if (!line[*i + 1] || (!ft_isalnum(line[*i + 1])
			&& line[*i + 1] != '_' && line[*i + 1] != '?'))
	{
		tmp = ft_substr_track(shell, line, *i, 1);
		*result = ft_strjoin_track(shell, *result, tmp);
		(*i)++;
		return ;
	}
	(*i)++;
	if (line[*i] == '?')
	{
		case_return(shell, result);
		(*i)++;
		return ;
	}
	*i += process_expand(shell, result, &line[*i]);
	if (line[*i] == ' ')
	{
		tmp = ft_substr_track(shell, line, *i, 1);
		*result = ft_strjoin_track(shell, *result, tmp);
		(*i)++;
	}
}
