/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:56:47 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/22 19:26:34 by arotondo         ###   ########.fr       */
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
		{
			perror("Invalid fd");
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirect_setup(t_exec *exec, t_redir *redir)
{
	if (!redir)
		if_no_redirection(exec);
	else
	{
		fprintf(stderr, "redir->type = %d\n", redir->type);
		if_redirection(exec);
	}
	redir = redir->next;
	// if (redir->next != NULL)
	clear_pipe(exec);
	return (0);
}

int	if_redirection(t_exec *exec)
{
	fprintf(stderr, "if_redirection\n");
	if (exec->infile != -1)
	{
		fprintf(stderr, "infile = %d\n", exec->infile);
		if (dup2(exec->infile, STDIN_FILENO) < 0)
		{
			perror("dup2a failed");
			exit(EXIT_FAILURE);
		}
		close(exec->infile);
		// fprintf(stderr, "exec->infile1 = %d\n", exec->infile);
		exec->infile = -1;
		// fprintf(stderr, "exec->infile2 = %d\n", exec->infile);
		// fprintf(stderr, "pipe[0] = %d\n", exec->pipe[0]);
		// fprintf(stderr, "pipe[1] = %d\n", exec->pipe[1]);
		// if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
		// {
		// 	perror("dup2b failed");
		// 	exit(EXIT_FAILURE);
		// }
	}
	else if (exec->outfile != -1)
	{
		fprintf(stderr, "outfile = %d\n", exec->outfile);
		if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		{
			perror("dup2c failed");
			exit(EXIT_FAILURE);
		}
		close(exec->outfile);
		exec->outfile = -1;
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
		{
			perror("dup2d failed");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	if_no_redirection(t_exec *exec)
{
	fprintf(stderr, "no redirection\n");
	if (exec->pipe[0] != -1)
	{
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
		{
			perror("dup2e failed");
			exit(EXIT_FAILURE);
		}
	}
	if (exec->pipe[1] != -1 && exec->last_cmd == false)
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
		{
			perror("dup2f failed");
			exit(EXIT_FAILURE);
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
	if (exec->infile > 0)
		close(exec->infile);
	if (exec->outfile > 0)
		close(exec->outfile);
}
