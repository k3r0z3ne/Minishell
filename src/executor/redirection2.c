/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:27:01 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/29 14:19:16 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	redirect_setup(t_shell *shell)
{
	if (shell->cmd->redirs->type == END)
		if_no_redirection(shell->exec);
	while (shell->cmd->redirs && shell->cmd->redirs->type != END)
	{
		if (shell->cmd->redirs->type == REDIRIN)
			if_infile(shell, shell->exec, shell->cmd->redirs);
		if_outfile(shell, shell->exec, shell->cmd->redirs);
		shell->cmd->redirs = shell->cmd->redirs->next;
		// fprintf(stderr, "HERE\n");
	}
	return (0);
}
int	if_infile(t_shell *shell, t_exec *exec, t_redir *redir)
{
	if (redir->type == REDIRIN)
	{
		if (shell->cmd->in_count)
			close(exec->infile);
		exec->infile = open(redir->file, O_RDONLY, 0664);
		if (exec->infile < 0)
		{
			perror("Invalid infile");
			exit(EXIT_FAILURE);
		}
		if (dup2(exec->infile, STDIN_FILENO) < 0)
		{
			perror("dup2a failed");
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "dup infile\n");
		close(exec->infile);
		shell->cmd->in_count--;
	}
	fprintf(stderr, "if infile OK\n");
	return (0);
}

int	if_outfile(t_shell *shell, t_exec *exec, t_redir *redir)
{
	if (redir->type == REDIROUT)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (redir->type == APPEND)
		exec->outfile = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (redir->type == HEREDOC)
		handle_here_doc(shell);
	else
		return (0);
	if (exec->outfile < 0)
	{
		perror("Invalid outfile");
		exit(EXIT_FAILURE);
	}
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
	{
		perror("dup2c failed");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "dup outfile\n");
	close(exec->outfile);
	// if (exec->last_cmd == false)
	// {
	// 	if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
	// 	{
	// 		perror("dup2d failed");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// close(exec->pipe[0]);
	fprintf(stderr, "if outfile OK\n");
	return (0);
}

int	if_no_redirection(t_exec *exec)
{
	if (exec->pipe[0] != -1)
	{
		fprintf(stderr, "dup pipe[0]\n");
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
		{
			perror("dup2e failed");
			exit(EXIT_FAILURE);
		}
		close(exec->pipe[0]);
	}
	// if (exec->pipe[1] != -1 && exec->last_cmd == false)
	// {
	// 	fprintf(stderr, "dup pipe[1]\n");
	// 	if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
	// 	{
	// 		perror("dup2f failed");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	close(exec->pipe[1]);
	// 	exec->pipe[1] = -1;
	// }
	fprintf(stderr, "if_no_redirection OK\n");
	return (0);
}

void	clear_pipe(t_shell *shell, int i)
{
	if (i < shell->exec->cmd_count - 1)
	{
		close(shell->exec->pipe[0]);
		close(shell->exec->pipe[1]);
	}
	// shell->exec->pipe[0] = -1;
	// shell->exec->pipe[1] = -1;
}
