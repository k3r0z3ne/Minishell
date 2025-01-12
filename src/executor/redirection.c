/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:56:47 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/12 18:07:01 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	redirection_check(t_shell *shell, t_cmd *cmd, t_redir *redirs)
{
	if (!redirs)
		return ;
	while (redirs)
	{
		if (redirs->type == 5)
			cmd->infile = open(redirs->file, O_RDONLY, 0664);
		else if (redirs->type == 6)
			cmd->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (redirs->type == 7)
			cmd->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (redirs->type == 8)
		{
			cmd->flag_hd = true;
			handle_here_doc(shell, cmd);
		}
		else
		{
			cmd->infile = -1;
			cmd->outfile = -1;
		}
		redirs = redirs->next;
	}
}

void	is_redir(t_cmd *cmd)
{
	// printf("is redir -> infile : %d\n", cmd->infile);
	// printf("is redir -> outfile : %d\n", cmd->outfile);
	if (cmd->infile != -1 && cmd->flag_hd == false)
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
		{
			printf("INFILE\n");
			return ;
		}
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
		{
			printf("OUTFILE\n");
			return ;
		}
	}
}

void	redirect_setup(t_cmd *cmd, int i, int count)
{
	if (i == 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
			return ;
		if (dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2b");
		// clear_pipe(cmd);
	}
	else if (i == count - 1)
	{
		if (dup2(cmd->pipe[0], STDIN_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2c");
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2d");
		// clear_pipe(cmd);
	}
	else
	{
		if (dup2(cmd->pipe[0], STDIN_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2e");
		if (dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2f");
		// clear_pipe(cmd);
	}
}

void	clear_pipe(t_cmd *cmd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (cmd->pipe[i])
		{
			close(cmd->pipe[0]);
			close(cmd->pipe[1]);
		}
		i++;
	}
	if (cmd->infile)
		close(cmd->infile);
	if (cmd->outfile)
		close(cmd->outfile);
}
