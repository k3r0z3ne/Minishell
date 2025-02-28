/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/28 14:49:40 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	errno_status(void)
{
	if (errno == 13)
		return (126);
	else
		return (127);
}

void	exec_cmd(t_shell *shell)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = find_path(shell);
	if (!tmp)
	{
		shell->last_status = errno_status();
		err_message(shell, shell->cmd->full_cmd[0], NULL, NULL);
	}
	path = check_path(shell, shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		shell->last_status = errno_status();
		if (shell->last_status != 127)
			err_message(shell, shell->cmd->full_cmd[0], NULL, NULL);
		else
			err_message(shell, shell->cmd->full_cmd[0], NULL, "command not found");

	}
	execve(path, shell->cmd->full_cmd, shell->envp);
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
			return (shell->last_status);
	}
	else
		return (0);
	if (shell->exec->cmd_count == 1 && is_builtin(shell) == true)
	{
		if (dup2(shell->exec->tty_fd0, STDIN_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
		if (dup2(shell->exec->tty_fd1, STDOUT_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
	}
	return (shell->last_status);
}
