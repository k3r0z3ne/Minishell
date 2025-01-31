/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/31 16:44:23 by arotondo         ###   ########.fr       */
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
		fprintf(stderr, "infile status in cmd nb: %d = %d\n", i + 1, is_fd_open(shell->exec->infile));
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
		fprintf(stderr, "builtin_less = %d\n", shell->exec->builtin_less);
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
		{
			perror("Creation pipe failed");
			exit(EXIT_FAILURE);
		}
		// printf("PIPE\n");
	}
	return (0);
}
