/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:56:47 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/28 17:10:49 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirection_check(t_shell *shell, t_exec *exec, t_redir *redirs)
{
	if (!redirs)
		return (0);
	while (redirs)
	{
		if (redirs->type == REDIRIN)
		{
			if (exec->infile != 0)
				close(exec->infile);
			exec->infile = open(redirs->file, O_RDONLY, 0664);
		}
		else if (redirs->type == REDIROUT)
			exec->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (redirs->type == APPEND)
			exec->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (redirs->type == HEREDOC)
			handle_here_doc(shell);
		if (exec->infile < 0 || exec->outfile < 0)
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}

int	redirect_setup(t_exec *exec, t_redir *redir)
{
	if (redir)
	{
		if (redir->type == REDIRIN)
		{
			close(exec->pipe[0]);
			if (dup2(exec->infile, STDIN_FILENO) < 0)
				return (-1);
			close(exec->infile);
			if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
				return (-1);
		}
		else if (redir->type == REDIROUT)
		{
			close(exec->pipe[1]);
			if (dup2(exec->outfile, STDOUT_FILENO) < 0)
				return (-1);
			close(exec->outfile);
			if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
				return (-1);
		}
	}
	else
	{
		if (exec->pipe[0] != -1)
		{
			if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
				return (-1);
			close(exec->pipe[0]);
		}
		if (exec->pipe[1] != -1 && exec->last_cmd == false)
		{
			if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
				return (-1);
			close(exec->pipe[1]);
		}
	}
	return (0);
}

void	is_redir(t_exec *exec, t_cmd *cmd)
{
	if (exec->infile != -1 && cmd->flag_hd == false)
	{
		if (dup2(exec->infile, STDIN_FILENO) < 0)
			return ;
	}
	if (exec->outfile != -1)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) < 0)
			return ;
	}
}

void	clear_pipe(t_exec *exec)
{
	if (exec->pipe[0] > 0)
		close(exec->pipe[0]);
	if (exec->pipe[1] > 0)
		close(exec->pipe[1]);
	if (exec->infile)
		close(exec->infile);
	if (exec->outfile)
		close(exec->outfile);
}
