/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:24:24 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/09 14:37:28 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_shell *shell)
{
	int	i;

	shell->pipe = (int **)malloc(sizeof(int *) * (shell->nb_cmd - 1));
	if (!shell->pipe)
		error("pipe array's allocation failed", shell);
	i = -1;
	while (++i < shell->nb_cmd - 1)
	{
		shell->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!shell->pipe[i])
			error("pipe's allocation failed", shell);
		if (pipe(shell->pipe[i]) < 0)
			error("pipe call failed");
	}
}

void	init_shell(t_shell *shell, char **argv, char **envp)
{
	shell->argv = argv;
	if (envp[0] == NULL || !envp)
		handle_empty_env(shell);
	else
		shell->envp = envp;
	shell->infile = -1;
	shell->outfile = -1;
	shell->nb_cmd = tokenizer();
	init_pipes(shell);
}
