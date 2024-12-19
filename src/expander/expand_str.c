/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:00:24 by witong            #+#    #+#             */
/*   Updated: 2024/12/19 12:44:58 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int append_until_var(char **result, char *str, int i)
{
	int		start;
	char	*s1;
	char	*tmp;

	start = i;
	while (str[i] && str[i] != '$')
		i++;
	if (start < i)
	{
		s1 = ft_substr(str, start, i - start);
		if (!s1)
			return (-1);
		tmp = ft_strjoin(*result, s1);
		free(s1);
		if (!tmp)
			return (-1);
		*result = tmp;
	}
	return (i);
}

static int expand_var(t_shell *shell, char **result, char *str, int i)
{
	int		start;
	char	*s1;
	char	*path;
	char	*tmp;

	i++;
	start = i;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
		i++;
	s1 = ft_substr(str, start, i - start);
	if (!s1)
		return (-1);
	path = ft_getenv(s1, shell->envp);
	free(s1);
	if (!path)
		path = ft_strdup("");
	tmp = ft_strjoin(*result, path);
	if (!tmp)
		return (-1);
	*result = tmp;
	return (i);
}

static void	process_expand_str(t_shell *shell, char **result, char *value)
{
	int	i;
	int	pos;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			pos = expand_var(shell, result, value, i);
			if (pos == -1)
				break ;
			i = pos;
		}
		else
		{
			pos = append_until_var(result, value, i);
			if (pos == -1)
				break ;
			i = pos;
		}
	}
}

void	expand_str(t_shell *shell, t_token *token)
{
		char	*result;

		result = ft_strdup("");
		if (!token->value || !result)
			return ;
		if (token->value[0] == '$' && token->value[1] == '?')
		{
			printf("$?");
			// case_return(token);
			return ;
		}
		process_expand_str(shell, &result, token->value);
		free(token->value);
		token->value = result;
}
