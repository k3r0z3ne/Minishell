/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/30 17:09:20 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int is_fd_open(int fd)
{
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

int	setup_old_pipe(t_exec *exec)
{
	// fprintf(stderr, "old pipe status : %d\n", is_fd_open(exec->old_pipe));
	if (exec->old_pipe != -1)
	{
		if (dup2(exec->old_pipe, STDIN_FILENO) < 0)
		{
			perror("dup2o failed");
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "dup old_pipe\n");
		close(exec->old_pipe);
	}
	if (exec->last_cmd == false)
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
		{
			perror("dup2p failed");
			exit(EXIT_FAILURE);
		}
		close(exec->pipe[1]);
	}
	return (0);
}

int	wait_process(t_shell *shell, int n)
{
	int		i;
	int		status;
	int		exit_status;

	i = 0;
	status = 0;
	exit_status = 0;
	while (i < n)
	{
		if (shell->exec->pids[i] > 0)
		{
			// printf("i in wait_process = %d\n", i);
			if (waitpid(shell->exec->pids[i], &status, 0) < 0)
				return (-1);
			printf("Waiting for PID %d\n", shell->exec->pids[i]);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
			shell->exec->pids[i] = -1;
			// printf("nb de passage\n");:
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
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
