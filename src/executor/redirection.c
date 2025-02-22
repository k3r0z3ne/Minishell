/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:27:01 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/22 16:32:45 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirect_setup(t_shell *shell, t_exec *exec, t_redir *redir)
{
	while (redir)
	{
		perror("redirection");
		if (redir->type == REDIRIN || redir->type == HEREDOC)
			if_infile(shell, exec, redir);
		if_outfile(shell, exec, redir);
		if (exec->last_cmd == false)
		{
			if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
				err_exit(shell, "dup2j failed");
			close(exec->pipe[0]);
		}
		redir = redir->next;
	}
	return (0);
}

int	if_infile(t_shell *shell, t_exec *exec, t_redir *redir)
{
	perror("infile");
	if (redir->type == HEREDOC)
		process_heredoc(shell);
	else if (redir->type == REDIRIN)
	{
		exec->infile = open(redir->file, O_RDONLY, 0664);
		if (exec->infile < 0)
			err_exit(shell, "Invalid infile");
		if (dup2(exec->infile, STDIN_FILENO) < 0)
			err_exit(shell, "dup2a failed");
		close(exec->infile);
	}
	return (0);
}

int	if_outfile(t_shell *shell, t_exec *exec, t_redir *redir)
{
	if (redir->type == REDIROUT)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (redir->type == APPEND)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		return (0);
	if (exec->outfile < 0)
		err_exit(shell, "Invalid outfile");
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		err_exit(shell, "dup2c failed");
	close(exec->outfile);
	close(exec->pipe[1]);
	exec->pipe[1] = 0;
	return (0);
}
