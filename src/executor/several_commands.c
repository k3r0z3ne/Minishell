/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/19 11:30:16 by arotondo         ###   ########.fr       */
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
			exec_builtin(shell);
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
	fprintf(stderr, "old_pipe -> %d\n", is_fd_open(shell->exec->old_pipe));
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	init_pids(shell);
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		count_fds(shell);
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		make_pipes(shell);
		fprintf(stderr, "%d\n", i + 1);
		shell->exec->pids[i] = process(shell);
		shell->cmd = shell->cmd->next;
		i++;
	}
	ignore_ctrl_c();
	shell->last_status = wait_process(shell, shell->exec->cmd_count);
	return (shell->last_status);
}

int	make_pipes(t_shell *shell)
{
	if (shell->exec->last_cmd == false)
	{
		if (pipe(shell->exec->pipe) < 0)
			err_exit("Creation pipe failed");
		fprintf(stderr, "pipe[0] = %d\n", shell->exec->pipe[0]);
		fprintf(stderr, "pipe[1] = %d\n", shell->exec->pipe[1]);
		shell->exec->if_pipe = true;
	}
	return (0);
}
