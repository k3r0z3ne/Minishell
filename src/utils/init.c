/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:34:29 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/19 11:54:54 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->argc = argc;
	shell->argv = argv;
	shell->last_status = 0;
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
			err_exit(shell, "Memory allocation failed");
	}
}
