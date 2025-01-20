/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:56:47 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/20 17:00:00 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirection_check(t_shell *shell, t_exec *exec, t_redir *redirs)
{
	if (!redirs)
		return (0);
	while (redirs)
	{
		if (redirs->type == 5)
			exec->infile = open(redirs->file, O_RDONLY, 0664);
		else if (redirs->type == 6)
			exec->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (redirs->type == 7)
			exec->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (redirs->type == 8)
			handle_here_doc(shell);
		if (exec->infile < 0 || exec->outfile < 0)
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}

int	redirect_setup(t_exec *exec, t_redir *redir)
{
	if (!redir)
	{
		// printf("REDIR INTERFILE\n");
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			return (-1);
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
	}
	else if (redir->type == REDIRIN)
	{
		// printf("REDIR INFILE\n");
		if (dup2(exec->infile, STDIN_FILENO) < 0)
			return (-1);
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(exec->pipe[0]);
	}
	else if (redir->type == REDIROUT)
	{
		// printf("REDIR OUTFILE\n");
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			return (-1);
		if (dup2(exec->outfile, STDOUT_FILENO) < 0)
			return (-1);
		close(exec->pipe[1]);
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

void	clear_pipe(t_exec *exec, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (exec->pipe[i])
		{
			close(exec->pipe[0]);
			close(exec->pipe[1]);
		}
		i++;
	}
	if (exec->infile)
		close(exec->infile);
	if (exec->outfile)
		close(exec->outfile);
}
