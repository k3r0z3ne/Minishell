/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:56:47 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/22 16:36:56 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirection_check(t_shell *shell, t_exec *exec)
{
	t_redir	*tmp;

	tmp = shell->cmd->redirs;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->type == REDIRIN)
			exec->infile = open(tmp->file, O_RDONLY, 0664);
		else if (tmp->type == REDIROUT)
			exec->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == APPEND)
			exec->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (tmp->type == HEREDOC)
			handle_here_doc(shell);
		if (exec->infile < 0 || exec->outfile < 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	redirect_setup(t_exec *exec, t_redir *redir)
{
	if (redir)
	{
		if (redir->type == REDIRIN)
		{
			// close(exec->pipe[0]);
			printf("infile = %d\n", exec->infile);
			if (dup2(exec->infile, STDIN_FILENO) < 0)
			{
				perror("dup2a failed");
				exit(EXIT_FAILURE);
			}
			close(exec->infile);
			close(exec->pipe[1]);
			// if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			// {
			// 	perror("dup2b failed");
			// 	exit(EXIT_FAILURE);
			// }
		}
		else if (redir->type == REDIROUT)
		{
			// close(exec->pipe[1]);
			printf("outfile = %d\n", exec->outfile);
			if (dup2(exec->outfile, STDOUT_FILENO) < 0)
			{
				perror("dup2c failed");
				exit(EXIT_FAILURE);
			}
			close(exec->outfile);
			// if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			// {
			// 	perror("dup2dfailed");
			// 	exit(EXIT_FAILURE);
			// }
		}
	}
	else
	{
		if (exec->pipe[0] != -1)
		{
			if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			{
				perror("dup2e failed");
				exit(EXIT_FAILURE);
			}
			close(exec->pipe[0]);
		}
		if (exec->pipe[1] != -1 && exec->last_cmd == false)
		{
			if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			{
				perror("dup2f failed");
				exit(EXIT_FAILURE);
			}
			close(exec->pipe[1]);
		}
	}
	return (0);
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
