/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:27:01 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 14:25:54 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirect_setup(t_shell *shell, t_exec *exec, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIRIN)
			if_infile(shell, exec, redir);
		else if (redir->type == REDIROUT || redir->type == APPEND)
			if_outfile(shell, exec, redir);
		else if (exec->last_cmd == false && exec->pipe[0] != 0)
		{
			if (shell->cmd->flag_hd == false)
			{
				perror("STEP1");
				if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
					err_message(shell, "redirection error", NULL, NULL);
				close(exec->pipe[0]);
				exec->pipe[0] = 0;
			}
		}
		redir = redir->next;
	}
	return (0);
}

int	if_infile(t_shell *shell, t_exec *exec, t_redir *redir)
{
	if (redir->type == REDIRIN)
	{
		exec->infile = open(redir->file, O_RDONLY, 0664);
		if (exec->infile < 0)
		{
			shell->last_status = 1;
			err_message(shell, redir->file, NULL, NULL);
		}
		shell->cmd->in_count--;
		if (!shell->cmd->in_count)
		{
			if (dup2(exec->infile, STDIN_FILENO) < 0)
				err_message(shell, "redirection error", NULL, NULL);
			if (close(exec->pipe[0]) < 0)
				err_message(shell, "close", NULL, NULL);
			exec->pipe[0] = 0;
		}
		if (close(exec->infile) < 0)
			err_message(shell, "close", NULL, NULL);
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
		err_message(shell, redir->file, NULL, NULL);
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		err_message(shell, "redirection error", NULL, NULL);
	close(exec->outfile);
	close(exec->pipe[1]);
	exec->pipe[1] = 0;
	return (0);
}
