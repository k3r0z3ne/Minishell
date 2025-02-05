/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:34:29 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/05 18:36:50 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->argc = argc;
	shell->argv = argv;
	if (!envp[0])
		shell->envp = mini_env();
	else
		shell->envp = arraydup(envp);
	shell->token = NULL;
	shell->cmd = NULL;
	shell->exec = NULL;
	shell->clean = NULL;
}

void	init_pids(t_shell *shell)
{
	if (shell->exec->builtin_less != 0)
	{
		shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * shell->exec->builtin_less);
		fprintf(stderr, "cmd_count = %d\n", shell->exec->cmd_count);
		if (!shell->exec->pids)
			err_exit("Memory allocation failed");
	}
}
