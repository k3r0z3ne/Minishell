/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/22 00:07:00 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_process(t_exec *exec, t_redir *redir)
{
	if (redir)
	{
		if (redir->type == REDIRIN)
			close(exec->infile);
		else if (redir->type == REDIROUT)
			close(exec->outfile);
	}
	else
	{
		if (exec->pipe[0] != -1)
			close(exec->pipe[0]);
		if (exec->pipe[1] != -1)
			close(exec->pipe[1]);
	}
}

int	setup_old_pipe(t_exec *exec, int idx, int old_pipe)
{
	if (old_pipe != -1)
	{
		if (dup2(old_pipe, STDIN_FILENO) < 0)
			return (-1);
		close(old_pipe);
	}
	if (idx < exec->cmd_count - 1)
	{
		close(exec->pipe[0]);
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(exec->pipe[1]);
	}
	return (0);
}

int	make_pipes(t_shell *shell, int i)
{
	if (i < shell->exec->cmd_count - 1)
	{
		// printf("PIPE\n");
		if (pipe(shell->exec->pipe) < 0)
			return (-1);
	}
	return (0);
}

int	wait_process(t_shell *shell, int n)
{
	int		i;
	int		status;

	i = 0;
	while (i < n)
	{
		if (shell->exec->pids[i] > 0)
		{	
			// printf("i in wait_process = %d\n", i);
			printf("Waiting for PID: %d\n", shell->exec->pids[i]);
			if (waitpid(shell->exec->pids[i], &status, WNOHANG) < 0)
				return (-1);
			if (WIFEXITED(status))
				printf("Child %d exited with status %d\n", shell->exec->pids[i], WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				printf("Child %d was terminated by signal %d\n", shell->exec->pids[i], WTERMSIG(status));
			shell->exec->pids[i] = -1;
			// printf("nb de passage\n");
		}
		i++;
	}
	return (status);
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
