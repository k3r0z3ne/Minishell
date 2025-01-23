/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/23 17:02:08 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	process(t_shell *shell, int i)
{
	int		old_pipe;
	pid_t	ret;

	old_pipe = -1;
	ret = fork();
	if (ret < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (ret == 0)
	{
		setup_old_pipe(shell->exec, i, old_pipe);
		redirect_setup(shell->exec, shell->cmd->redirs);
		exec_cmd(shell);
	}
	if (old_pipe != -1)
		close(old_pipe);
	if (i < shell->exec->cmd_count - 1)
	{
		close(shell->exec->pipe[1]);
		old_pipe = shell->exec->pipe[0];
	}
	// if (ret > 0)
	// 	clear_pipe(shell->exec);
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;
	int	exit_status;

	shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * how_much_cmd(shell));
	if (!shell->exec->pids)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	exit_status = 0;
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		redirection_check(shell, shell->exec);
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		make_pipes(shell, i);
		if (is_builtin(shell) == true)
		{
			exit_status = exec_builtin(shell);
			return (exit_status);
		}
		else
			shell->exec->pids[i] = process(shell, i);
		// printf("cmd : %s\n", shell->cmd->full_cmd[0]);
		// printf("i = %d\n", i);
		shell->cmd = shell->cmd->next;
		i++;
	}
	exit_status = wait_process(shell, how_much_cmd(shell));
	return (exit_status);
}

void	parent_process(t_exec *exec, t_redir *redir)
{
	while (redir)
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
		redir = redir->next;
	}
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
