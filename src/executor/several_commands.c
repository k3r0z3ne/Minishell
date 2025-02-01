/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/01 17:48:40 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	process(t_shell *shell, int i)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		err_exit("Fork failed");
	else if (ret == 0)
	{
		activate_ctrl_c();
		activate_ctrl_backslash();
		redirect_setup(shell);
		setup_old_pipe(shell->exec);
		if (is_forkable(shell) == true)
			exec_builtin(shell);
		else
			exec_cmd(shell);
	}
	if (shell->exec->old_pipe != -1)
		close(shell->exec->old_pipe);
	if (i < shell->exec->cmd_count - 1)
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
		make_pipes(shell, i);
		if (is_builtin(shell) == true)
			exec_builtin(shell);
		else
			shell->exec->pids[i] = process(shell, i);
		shell->cmd = shell->cmd->next;
		i++;
	}
	exit_status = wait_process(shell, shell->exec->builtin_less);
	return (exit_status);
}

int	make_pipes(t_shell *shell, int i)
{
	if (i < shell->exec->cmd_count - 1)
	{
		if (pipe(shell->exec->pipe) < 0)
			err_exit("Creation pipe failed");
	}
	return (0);
}
