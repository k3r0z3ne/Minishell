/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2024/12/16 16:35:55 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, envp);
	while (1)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)
			break ;
		if (*shell->input != '\0')
			add_history(shell->input);
		shell->token = lexer(shell->input);
		shell->cmd = parser(shell->token);
		print_tokens(shell->token);
		print_table(shell->cmd);
		print_redirs(shell->cmd);
	}
	rl_clear_history();
	return (0);
}
