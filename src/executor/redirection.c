/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:27:01 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/04 16:25:28 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirect_setup(t_shell *shell, t_exec *exec, t_redir *redirs)
{
	// if (shell->cmd->redirs->type == END)
	// 	if_no_redirection(shell->exec);
	while (redirs)
	{
		if (redirs->type == REDIRIN || redirs->type == HEREDOC)
			if_infile(shell, exec, redirs);
		if_outfile(exec, redirs);
		redirs = redirs->next;
	}
	return (0);
}

int	if_infile(t_shell *shell, t_exec *exec, t_redir *redir)
{
	if (redir->type == REDIRIN)
	{
		if (shell->cmd->in_count)
		{
			exec->infile = open(redir->file, O_RDONLY, 0664);
			if (exec->infile < 0)
				err_exit("Invalid infile");
		}
		shell->cmd->in_count--;
	}
	else if (redir->type == HEREDOC)
		handle_here_doc(shell);
	if (dup2(exec->infile, STDIN_FILENO) < 0)
		err_exit("dup2a failed");
	close(exec->infile);
	return (0);
}

int	if_outfile(t_exec *exec, t_redir *redir)
{
	if (redir->type == REDIROUT)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (redir->type == APPEND)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		return (0);
	if (exec->outfile < 0)
		err_exit("Invalid outfile");
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		err_exit("dup2c failed");
	close(exec->outfile);
	close(exec->pipe[1]);
	exec->pipe[1] = 0;
	return (0);
}

// int	if_no_redirection(t_exec *exec)
// {
// 	if (exec->last_cmd == false)
// 	{
// 		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
// 			err_exit("dup2e failed");
// 		close(exec->pipe[0]);
// 		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
// 			err_exit("dup2p failed");
// 		close(exec->pipe[1]);
// 	}
// 	return (0);
// }
