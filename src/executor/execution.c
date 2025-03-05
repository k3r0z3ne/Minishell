/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 14:22:51 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_cmd(t_shell *shell)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = find_path(shell);
	if (!tmp)
		err_message(shell, shell->cmd->full_cmd[0], NULL, NULL);
	path = check_path(shell, shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
		err_message(shell, shell->cmd->full_cmd[0], NULL, NULL);
	execve(path, shell->cmd->full_cmd, shell->envp);
}

void	tty_handler(t_shell *shell)
{
	if (shell->exec->tty_fd0 != -1)
	{
		if (dup2(shell->exec->tty_fd0, STDIN_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
		close(shell->exec->tty_fd0);
		shell->exec->tty_fd0 = -1;
	}
	if (shell->exec->tty_fd1 != -1)
	{
		if (dup2(shell->exec->tty_fd1, STDOUT_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
		close(shell->exec->tty_fd1);
		shell->exec->tty_fd1 = -1;
	}
}

void	only_infile(t_shell *shell)
{	
	shell->exec->infile = open(shell->cmd->redirs->file, O_RDONLY, 0664);
	if (shell->exec->infile < 0)
	{
		shell->last_status = 1;
		err_message2(shell->cmd->redirs->file, NULL, NULL);
	}
	close(shell->exec->infile);
}

int	main_exec(t_shell *shell)
{
	shell->exec->cmd_count = count_cmd(shell->cmd);
	shell->exec->builtin_less = how_much_cmd(shell);
	if (shell->exec->cmd_count > 1)
		shell->last_status = several_cmds(shell);
	else if (shell->exec->cmd_count == 1)
		shell->last_status = only_cmd(shell);
	else if (!shell->exec->cmd_count && shell->cmd->redirs->type == HEREDOC)
	{
		if (iter_heredoc(shell) == 2)
		{
			tty_handler(shell);
			return (shell->last_status);
		}
	}
	else if (shell->cmd->redirs->type == REDIRIN)
		only_infile(shell);
	tty_handler(shell);
	return (shell->last_status);
}
