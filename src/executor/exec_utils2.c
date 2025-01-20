/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:37:01 by xenon             #+#    #+#             */
/*   Updated: 2025/01/20 15:59:12 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int exec_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->full_cmd[0], "echo"))
		shell->exec->exit_status = ft_echo(count_line \
		(shell->cmd->full_cmd), shell->cmd->full_cmd, shell->envp);
	// else if (!ft_strcmp(shell->cmd->full_cmd[0], "cd"))
		// shell->exec->exit_status = ft_cd(shell->cmd->full_cmd[1], shell->envp);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "pwd"))
		shell->exec->exit_status = ft_pwd(shell->argc);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "export"))
		shell->exec->exit_status = ft_export(shell);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "unset"))
		shell->exec->exit_status = ft_unset(shell);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "env"))
		shell->exec->exit_status = ft_env(shell->envp);
	// else if (!ft_strcmp(shell->cmd->full_cmd[0], "exit"))
	// {
	// 	shell->exec->exit_status = 0;
	// 	ft_exit(shell->cmd->full_cmd, shell->exec->exit_status);
	// }
	return (shell->exec->exit_status);
}

bool	is_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->full_cmd[0], "echo"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "cd"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "pwd"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "export"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "unset"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "env"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "exit"))
		return (true);
	else
		return (false);
}
