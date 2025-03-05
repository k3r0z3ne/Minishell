/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:24:42 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 13:14:59 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirect_setup2(t_shell *shell, t_exec *exec, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIRIN)
			if_infile2(shell, exec, redir);
		else if (redir->type == REDIROUT || redir->type == APPEND)
			if_outfile2(shell, exec, redir);
		redir = redir->next;
	}
	return (0);
}

int	if_infile2(t_shell *shell, t_exec *exec, t_redir *redir)
{
	shell->exec->tty_fd0 = dup(STDIN_FILENO);
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
		}
		close(exec->infile);
	}
	return (0);
}

int	if_outfile2(t_shell *shell, t_exec *exec, t_redir *redir)
{
	shell->exec->tty_fd1 = dup(STDOUT_FILENO);
	if (redir->type == REDIROUT)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (redir->type == APPEND)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (exec->outfile < 0)
		err_message(shell, redir->file, NULL, NULL);
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		err_message(shell, "redirection error", NULL, NULL);
	if (close(exec->outfile) < 0)
		err_message(shell, "close", NULL, NULL);
	return (0);
}
