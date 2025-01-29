/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:46:38 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/29 12:28:58 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	only_cmd(t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	redirection_check(shell, shell->exec);
	shell->exec->pids = tracked_malloc(shell, sizeof(pid_t));
	if (!shell->exec->pids)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (is_builtin(shell) == true)
	{
		exit_status = exec_builtin(shell);
		return (exit_status);
	}
	shell->exec->pids[0] = fork();
	if (shell->exec->pids[0] < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (shell->exec->pids[0] == 0)
	{
		is_redir(shell, shell->cmd->redirs);
		exec_cmd(shell);
	}
	else if (shell->exec->pids[0] > 0 && shell->cmd->flag_hd == false)
		exit_status = wait_process(shell, 1);
	close_files(shell);
	return (exit_status);
}

void	is_redir(t_shell *shell, t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (shell->exec->infile != -1 && shell->cmd->flag_hd == false)
		{
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
			{
				perror("dup2 failed");
				exit(EXIT_FAILURE);
			}
			close(shell->exec->infile);
			shell->exec->infile = -1;
		}
		else if (shell->exec->outfile != -1)
		{
			if (dup2(shell->exec->outfile, STDOUT_FILENO) < 0)
			{
				perror("dup2 failed");
				exit(EXIT_FAILURE);
			}
			close(shell->exec->outfile);
			shell->exec->outfile = -1;
		}
		tmp = tmp->next;
	}
}

void	close_files(t_shell *shell)
{
	if (shell->exec->infile != 0)
		close(shell->exec->infile);
	if (shell->exec->outfile != 0)
		close(shell->exec->outfile);
}
