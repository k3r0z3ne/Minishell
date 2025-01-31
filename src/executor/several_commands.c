/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/30 16:56:13 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	process(t_shell *shell, int i)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (ret == 0)
	{
		activate_ctrl_c();
		activate_ctrl_backslash();
		redirect_setup(shell);
		fprintf(stderr, "infile status in cmd nb:%d = %d\n", i + 1, is_fd_open(shell->exec->infile));
		setup_old_pipe(shell->exec);
		exec_cmd(shell);
	}
	if (shell->exec->old_pipe != -1)
		close(shell->exec->old_pipe);
	if (i < shell->exec->cmd_count - 1)
	{
		close(shell->exec->pipe[1]);
		shell->exec->old_pipe = shell->exec->pipe[0];
		// close(shell->exec->pipe[0]);
	}
	fprintf(stderr, "command %i done.\n", i + 1);
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;
	int	exit_status;

	if (shell->exec->builtin_less != 0)
	{
		
		shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * shell->exec->builtin_less);
		if (!shell->exec->pids)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	exit_status = 0;
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		count_fds(shell);
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		make_pipes(shell, i);
		if (is_builtin(shell) == true)
		{
			exit_status = exec_builtin(shell);
			return (exit_status);
		}
		else
			shell->exec->pids[i] = process(shell, i);
		shell->cmd = shell->cmd->next;
		i++;
	}
	exit_status = wait_process(shell, how_much_cmd(shell));
	return (exit_status);
}

int	make_pipes(t_shell *shell, int i)
{
	if (i < shell->exec->cmd_count - 1)
	{
		if (pipe(shell->exec->pipe) < 0)
		{
			perror("Creation pipe failed");
			exit(EXIT_FAILURE);
		}
		// printf("PIPE\n");
	}
	return (0);
}
