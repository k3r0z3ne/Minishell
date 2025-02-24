/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/24 16:51:51 by witong           ###   ########.fr       */
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
		err_message(shell->cmd->full_cmd[0], NULL, "No such file or directory");
		err_exit(shell, 127);
	}
	path = check_path(shell, shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		err_message(shell->cmd->full_cmd[0], NULL, "No such file or directory");
		err_exit(shell, 127);
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
		process_heredoc(shell);
	else
		err_return("No command found");
	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	return (shell->last_status);
}
