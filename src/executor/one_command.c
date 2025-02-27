/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:46:38 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/27 22:49:27 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	process1(t_shell *shell)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		err_message(shell, "fork", NULL, NULL);
	else if (!ret)
	{
		setup_child_signals(shell);
		redirect_setup2(shell, shell->exec, shell->cmd->redirs);
		exec_cmd(shell);
	}
	return (ret);
}

int	only_cmd(t_shell *shell)
{
	count_fds(shell);
	if (g_signal < 0)
		return (shell->last_status);
	if (shell->exec->builtin_less != 0)
	{
		shell->exec->pids = tracked_malloc(shell, sizeof(pid_t));
		if (!shell->exec->pids)
			err_message(shell, "malloc", NULL, NULL);
	}
	if (shell->cmd->flag_hd == true)
	{
		if (iter_heredoc(shell) == 2)
			return (shell->last_status);
	}
	if (is_builtin(shell) == true)
	{
		redirect_setup2(shell, shell->exec, shell->cmd->redirs);
		exec_builtin(shell);
	}
	else
	{
		shell->exec->pids[0] = process1(shell);
		ignore_ctrl_c(shell);
		shell->last_status = wait_process(shell, shell->exec->builtin_less);
	}
	return (shell->last_status);
}
