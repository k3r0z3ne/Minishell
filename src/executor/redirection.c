/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:56:47 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/19 18:23:38 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	redirection_check(t_cmd *cmd, t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == 5)
			cmd->infile = open(tmp->file, O_RDONLY, 0664);
		else if (tmp->type == 6)
			cmd->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == 7)
			cmd->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (tmp->type == 8)
			cmd->infile = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0664);
		tmp = tmp->next;
	}
}

void	redirect_setup(t_cmd *cmd, int i, int n)
{
	
	if (i == 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2a");
		if (dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
			return ;
			// closerror(cmd, "dup2b");
		// clear_pipe(cmd);
	}
	else if (i == n - 1)
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
