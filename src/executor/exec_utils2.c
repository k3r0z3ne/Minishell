/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:16:33 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/07 13:26:00 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->full_cmd[0], "echo"))
		shell->exec->exit_status = ft_echo(count_line \
		(shell->cmd->full_cmd), shell->cmd->full_cmd, shell->envp);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "cd"))
	{
		if (!shell->cmd->full_cmd[1] || !shell->cmd->full_cmd[2])
			shell->exec->exit_status = ft_cd(shell, shell->cmd->full_cmd[1]);
		else
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	}
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
}

bool	is_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->full_cmd[0], "cd"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "echo"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "pwd"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "env"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "export"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "unset"))
		return (true);
	else if (!ft_strcmp(shell->cmd->full_cmd[0], "exit"))
		return (true);
	else
		return (false);
}

void	count_fds(t_shell *shell)
{
	t_redir	*tmp;

	tmp = shell->cmd->redirs;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->type == REDIRIN)
			shell->cmd->in_count++;
		else if (tmp->type == REDIROUT)
			shell->cmd->out_count++;
		else if (tmp->type == APPEND)
			shell->cmd->out_count++;
		else if(tmp->type == HEREDOC)
			shell->cmd->hd_count++;
		tmp = tmp->next;
	}
}
