/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/21 18:28:21 by arotondo         ###   ########.fr       */
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
