/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/07 13:50:55 by xenon            ###   ########.fr       */
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
		err_exit("$PATH not found");
	path = check_path(shell, shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
		err_exit("No command path found");
	execve(path, shell->cmd->full_cmd, shell->envp);
}

int	main_exec(t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	shell->exec->cmd_count = count_cmd(shell->cmd);
	shell->exec->builtin_less = how_much_cmd(shell);
	if (shell->exec->cmd_count > 1)
		exit_status = several_cmds(shell);
	else if (shell->exec->cmd_count == 1)
		exit_status = only_cmd(shell);
	else if (!shell->exec->cmd_count && shell->cmd->redirs->type == HEREDOC)
		handle_here_doc(shell);
	else
		err_return("No command found");
	unlink(".tmp.txt");
	return (exit_status);
}
