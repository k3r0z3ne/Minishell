/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/22 16:34:37 by arotondo         ###   ########.fr       */
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
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(old_pipe);
	}
	if (idx < exec->cmd_count - 1)
	{
		close(exec->pipe[0]);
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
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
		{
			perror("Creation pipe failed");
			exit(EXIT_FAILURE);
		}
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
			printf("Waiting for PID: %d\n", shell->exec->pids[i]);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
			shell->exec->pids[i] = -1;
			// printf("nb de passage\n");
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
