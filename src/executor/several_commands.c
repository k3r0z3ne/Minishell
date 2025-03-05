/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 14:24:32 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_pr(t_shell *shell)
{
	if (shell->exec->old_pipe != -1)
		close(shell->exec->old_pipe);
	if (shell->exec->last_cmd == false && shell->exec->pipe[1] != 0)
	{
		close(shell->exec->pipe[1]);
		shell->exec->old_pipe = shell->exec->pipe[0];
	}
	ft_exit(shell, shell->cmd->full_cmd);
}

pid_t	process(t_shell *shell)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		err_message(shell, "fork", NULL, "Resource temporarily unavailable");
	else if (ret == 0)
	{
		setup_child_signals(shell);
		redirect_setup(shell, shell->exec, shell->cmd->redirs);
		setup_old_pipe(shell, shell->exec);
		if (is_builtin(shell) == true)
			exec_builtin(shell);
		else
			exec_cmd(shell);
	}
	if (shell->exec->old_pipe != -1)
		close(shell->exec->old_pipe);
	if (shell->exec->last_cmd == false)
	{
		if (close(shell->exec->pipe[1]) < 0)
			err_message(shell, "close", NULL, "Bad file descriptor");
		shell->exec->old_pipe = shell->exec->pipe[0];
		perror("STEP3");
	}
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	init_pids(shell);
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		if (shell->cmd->flag_hd == true)
		{
			if (iter_heredoc(shell) == 2)
				return (shell->last_status);
		}
		count_fds(shell);
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		make_pipes(shell);
		shell->exec->pids[i] = process(shell);
		shell->cmd = shell->cmd->next;
		i++;
	}
	ignore_ctrl_c(shell);
	shell->last_status = wait_process(shell, shell->exec->cmd_count);
	return (shell->last_status);
}

int	make_pipes(t_shell *shell)
{
	if (shell->exec->last_cmd == false)
	{
		if (pipe(shell->exec->pipe) < 0)
			err_message(shell, "pipe", NULL, "Too many open files");
		shell->exec->if_pipe = true;
	}
	return (0);
}
