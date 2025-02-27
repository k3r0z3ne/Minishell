/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/27 23:27:15 by xenon            ###   ########.fr       */
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
	{
		shell->last_status = 127;
		err_message(shell, shell->cmd->full_cmd[0], NULL, "command not found");
	}
	path = check_path(shell, shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		shell->last_status = 127;
		err_message(shell, shell->cmd->full_cmd[0], NULL, "command not found");
	}
	execve(path, shell->cmd->full_cmd, shell->envp);
}

int	main_exec(t_shell *shell)
{
	int	tty_fd;

	tty_fd = 0;
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
	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		if (dup2(tty_fd, STDIN_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
		if (close(tty_fd) < 0)
			err_message(shell, "close", NULL, NULL);
	}
	return (shell->last_status);
}
