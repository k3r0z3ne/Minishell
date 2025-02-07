/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:46:38 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/07 13:54:37 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

pid_t	process1(t_shell *shell)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		err_exit("Fork failed");
	else if (!ret)
	{
		activate_ctrl_c();
		activate_ctrl_backslash();
		is_redir(shell, shell->cmd->redirs);
		exec_cmd(shell);
	}
	return (ret);
}

int	only_cmd(t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	redirection_check(shell, shell->exec);
	count_fds(shell);
	if (shell->exec->builtin_less != 0)
	{
		shell->exec->pids = tracked_malloc(shell, sizeof(pid_t));
		if (!shell->exec->pids)
			err_exit("Memory allocation failed");
	}
	if (is_builtin(shell) == true)
		exec_builtin(shell);
	else
	{
		shell->exec->pids[0] = process1(shell);
		ignore_ctrl_c();
		exit_status = wait_process(shell, shell->exec->builtin_less);
	}
	return (exit_status);
}

int	redirection_check(t_shell *shell, t_exec *exec)
{
	t_redir	*tmp;

	tmp = shell->cmd->redirs;
	if (tmp->type == END)
		return (0);
	while (tmp) 
	{
		if (tmp->type == REDIRIN)
		{
			if (shell->cmd->in_count)
				close(exec->infile);
			exec->infile = open(tmp->file, O_RDONLY, 0664);
			shell->cmd->in_count--;
		}
		else if (tmp->type == REDIROUT)
			exec->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == APPEND)
			exec->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else if (tmp->type == HEREDOC)
			handle_here_doc(shell);
		if (exec->infile < 0 || exec->outfile < 0)
			err_exit("Invalid fd");
		tmp = tmp->next;
	}
	return (0);
}

void	is_redir(t_shell *shell, t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == REDIRIN || tmp->type == HEREDOC)
		{
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
				err_exit("dup2 failed");
			close(shell->exec->infile);
		}
		else if (tmp->type == REDIROUT || tmp->type == APPEND)
		{
			if (dup2(shell->exec->outfile, STDOUT_FILENO) < 0)
				err_exit("dup2 failed");
			close(shell->exec->outfile);
		}
		tmp = tmp->next;
	}
}

void	close_files(t_shell *shell)
{
	if (shell->exec->infile != 0)
		close(shell->exec->infile);
	if (shell->exec->outfile != 0)
		close(shell->exec->outfile);
}
