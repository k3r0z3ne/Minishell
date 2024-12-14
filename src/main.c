/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 16:05:07 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(const char *name, char **envp)
{
	size_t	len;
	size_t	i;

	if (!envp || !*name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

int	count_line(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**arraydup(char **array)
{
	char	**dup;
	int		lc;

	lc = count_line(array);
	dup = (char **)malloc(sizeof(char*) * (lc + 1));
	if (!dup)
		return (NULL);
	dup[lc] = NULL;
	lc = 0;
	while (array[lc])
	{
		dup[lc] = ft_strdup(array[lc]);
		if (!dup[lc])
		{
			free_array(dup, lc);
			return (NULL);
		}
		lc++;
	}
	return (dup);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	(void) envp;
	char *input;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input != '\0')
			add_history(input);
		tokens = lexer(input);
		cmds = parser(tokens);
		print_tokens(tokens);
		print_table(cmds);
	}
	rl_clear_history();
	return (0);
}
