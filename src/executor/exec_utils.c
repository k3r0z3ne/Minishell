/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/20 13:09:34 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_process(t_exec *exec, t_redir *redir)
{
	printf("une fois ?\n");
	if (!redir)
	{
		printf("close pipes\n");
		close(exec->pipe[0]);
		close(exec->pipe[1]);
	}
	else if (redir->type == REDIRIN)
	{
		printf("close infile\n");
		close(exec->infile);
		close(exec->pipe[1]);
	}
	else if (redir->type == REDIROUT)
	{
		printf("close outfile\n");
		close(exec->pipe[0]);
		close(exec->outfile);
	}
	else
		printf("close nothing\n");
}

int	make_pipes(t_shell *shell, int i)
{
	if (i < shell->exec->cmd_count - 1)
	{
		if (pipe(shell->exec->pipe) < 0)
			return (-1);
	}
	return (0);
}

int	wait_process(t_shell *shell, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		// printf("nb de passage\n");
		if (waitpid(shell->exec->pids[i], &status, 0) < 0)
			return (-1);
		i++;
	}
	return (status);
}

int	is_builtin(t_shell *shell)
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
	else
		return (-1);
	return (shell->exec->exit_status);
}
int	count_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	if (!tmp)
		return (0);
	i = 1;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
