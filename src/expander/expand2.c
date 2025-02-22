/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:42:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/21 19:46:20 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

void	case_return(t_shell *shell, char **result)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(shell->last_status);
	if (!exit_status_str)
		return ;
	*result = ft_strjoin_track(shell, *result, exit_status_str);
	free(exit_status_str);
}

void	handle_dollar(t_shell *shell, char *line, int *i, char **result)
{
	char	*tmp;

	tmp = NULL;
	if (!line[(*i) + 1] || (!ft_isalnum(line[(*i) + 1]) && \
	line[(*i) + 1] != '_' && line[(*i) + 1] != '?'))
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
		while (value[i] && (ft_isalnum(value[i]) || \
		value[i] == '_' || value[i] == '?'))
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
