/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/07 13:56:27 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	process(t_shell *shell)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		err_exit("Fork failed");
	else if (ret == 0)
	{
		activate_ctrl_c();
		activate_ctrl_backslash();
		setup_old_pipe(shell->exec);
		redirect_setup(shell, shell->exec, shell->cmd->redirs);
		if (is_builtin(shell) == true)
		{
			exec_builtin(shell);
			exit(shell->exec->exit_status);
		}
		else
			exec_cmd(shell);
	}
	if (shell->exec->old_pipe != -1)
		close(shell->exec->old_pipe);
	if (shell->exec->last_cmd == false)
	{
		close(shell->exec->pipe[1]);
		shell->exec->old_pipe = shell->exec->pipe[0];
	}
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	init_pids(shell);
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		count_fds(shell);
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		make_pipes(shell);
		shell->exec->pids[i] = process(shell);
		shell->cmd = shell->cmd->next;
		i++;
	}
	ignore_ctrl_c();
	exit_status = wait_process(shell, shell->exec->cmd_count);
	return (exit_status);
}

int	make_pipes(t_shell *shell)
{
	if (shell->exec->last_cmd == false)
	{
		if (pipe(shell->exec->pipe) < 0)
			err_exit("Creation pipe failed");
	}
	return (0);
}
