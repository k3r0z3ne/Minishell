/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/07 14:00:46 by xenon            ###   ########.fr       */
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
		if (dup2(exec->old_pipe, STDIN_FILENO) < 0)
			err_exit("dup2o failed");
		close(exec->old_pipe);
	}
	if (exec->last_cmd == false && exec->pipe[1] != 0)
	{
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
	int		print_sigquit;

	if (!shell || !shell->exec || !shell->exec->pids)
		return (-1);
	i = 0;
	status = 0;
	exit_status = 0;
	print_sigquit = 0;
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
				if (!print_sigquit && WTERMSIG(status) == SIGQUIT)
				{
					ft_putstr_fd("Quit (core dumped)\n", 2);
					print_sigquit = 1;
				}
				exit_status = 128 + WTERMSIG(status);
			}
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
	if (!tmp || !tmp->full_cmd[0])
		return (0);
	i = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
