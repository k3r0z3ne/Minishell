/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/05 18:37:49 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int is_fd_open(int fd)
{
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

int	setup_old_pipe(t_exec *exec)
{
	if (exec->old_pipe != -1)
	{
		fprintf(stderr, "old_pipe = %d\n", is_fd_open(exec->old_pipe));
		if (dup2(exec->old_pipe, STDIN_FILENO) < 0)
			err_exit("dup2o failed");
		close(exec->old_pipe);
		fprintf(stderr, "old_pipe = %d\n", is_fd_open(exec->old_pipe));
	}
	if (exec->last_cmd == false && exec->pipe[1] != 0)
	{
		fprintf(stderr, "HERE\n");
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			err_exit("dup2p failed");
		close(exec->pipe[1]);
	}
	return (0);
}

int	wait_process(t_shell *shell, int n)
{
	int		i;
	int		status;
	int		exit_status;

	if (!shell || !shell->exec || !shell->exec->pids)
		return (-1);
	i = 0;
	status = 0;
	exit_status = 0;
	while (i < n)
	{
		if (shell->exec->pids[i] > 0)
		{
			if (waitpid(shell->exec->pids[i], &status, 0) < 0)
				err_exit("waitpid failed");
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				exit_status = 128 + WTERMSIG(status);
			}
			// shell->exec->pids[i] = -1;
		}
		i++;
	}
	return (exit_status);
}

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	if (!tmp)
		return (0);
	i = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
