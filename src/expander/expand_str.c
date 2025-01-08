/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:00:24 by witong            #+#    #+#             */
/*   Updated: 2025/01/08 13:42:19 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int append_until_var(t_shell *shell, char **result, char *str, int i)
{
	int		start;
	char	*s1;
	char	*tmp;

	start = i;
	while (str[i] && str[i] != '$')
		i++;
	if (start < i)
	{
		s1 = ft_substr_track(shell, str, start, i - start);
		if (!s1)
			return (-1);
		tmp = ft_strjoin(*result, s1);
		// free(s1);
		if (!tmp)
			return (-1);
		*result = tmp;
	}
	return (i);
}

static int	expand_var(t_shell *shell, char **result, char *str, int i)
{
	int		start;
	char	*s1;
	char	*path;
	char	*tmp;

	start = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'|| str[i] == '?'))
		i++;
	s1 = ft_substr_track(shell, str, start, i - start);
	if (!s1)
		return (-1);
	path = ft_getenv(s1, shell->envp);
	// free(s1);
	if (!path)
		path = ft_strdup_track(shell, "");
	tmp = ft_strjoin(*result, path);
	if (!tmp)
		return (-1);
	*result = tmp;
	return (i);
}

void	process_expand_str(t_shell *shell, char **result, char *value)
{
	int	i;
	int	pos;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			pos = expand_var(shell, result, value, i);
			if (pos == -1)
				break ;
			i = pos;
		}
		else
		{
			pos = append_until_var(shell, result, value, i);
			if (pos == -1)
				break ;
			i = pos;
		}
	}
}

void	expand_str(t_shell *shell)
{
	char	*result;
	char	*tmp;

	if (!shell || !shell->token || !shell->token->value)
		return ;
	if (shell->token->value[0] == '$' && shell->token->value[1] == '?')
	{
		printf("$?");
		// case_return(token);
		return ;
	}
	result = ft_strdup_track(shell, "");
	if (!result)
		return ;
	process_expand_str(shell, &result, shell->token->value);
	tmp = shell->token->value;
	shell->token->value = result;
	shell->token->type = WORD;
	free(tmp);
}
