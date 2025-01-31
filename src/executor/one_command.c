/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:46:38 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/30 17:17:56 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	only_cmd(t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	redirection_check(shell, shell->exec);
	count_fds(shell);
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
		activate_ctrl_c();
		activate_ctrl_backslash();
		is_redir(shell, shell->cmd->redirs);
		// redirect_setup(shell);
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
		if (tmp->type == REDIRIN && shell->cmd->flag_hd == false)
		{
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
			{
				perror("dup2 failed");
				exit(EXIT_FAILURE);
			}
			close(shell->exec->infile);
		}
		else if (tmp->type == REDIROUT)
		{
			if (dup2(shell->exec->outfile, STDOUT_FILENO) < 0)
			{
				perror("dup2 failed");
				exit(EXIT_FAILURE);
			}
			close(shell->exec->outfile);
		}
		tmp = tmp->next;
	}
}

int	redirection_check(t_shell *shell, t_exec *exec)
{
	t_redir	*tmp;

	tmp = shell->cmd->redirs;
	if (tmp->type == END)
		return (0);
	while (tmp)
	{
		if (tmp->type == REDIRIN)
		{
			if (exec->infile)
				close(exec->infile);
			exec->infile = open(tmp->file, O_RDONLY, 0664);
			shell->cmd->in_count--;
		}
		else if (tmp->type == REDIROUT)
			exec->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == APPEND)
			exec->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (tmp->type == HEREDOC)
			handle_here_doc(shell);
		if (exec->infile < 0 || exec->outfile < 0)
		{
			perror("Invalid fd");
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	close_files(t_shell *shell)
{
	if (shell->exec->infile != -1)
		close(shell->exec->infile);
	if (shell->exec->outfile != -1)
		close(shell->exec->outfile);
}
