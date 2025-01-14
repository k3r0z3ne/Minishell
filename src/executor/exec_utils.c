/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/14 18:13:34 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_process(t_exec *exec)
{
	if (exec->infile > 0)
	{
		close(exec->infile);
		close(exec->pipe[1]);
	}
	else if (exec->outfile > 0)
	{
		close(exec->pipe[0]);
		close(exec->outfile);
	}
	else
	{
		close(exec->pipe[0]);
		close(exec->pipe[1]);
	}
}

int	make_pipes(t_shell *shell, int i)
{
	if (i < shell->exec->cmd_count - 1)
	{
		shell->exec->pipe = (int *)malloc(sizeof(int) * 2);
		if (!shell->exec->pipe)
			return (-1);
		if (pipe(shell->exec->pipe) < 0)
			return (-1);
		shell->exec->is_pipe = true;
	}
	else
		shell->exec->is_pipe = false;
	return (0);
}

int	wait_process(t_shell *shell, int n)
{
	int	i;
	int	status;

	i = 0;
	// printf("max iter = %d\n", n);
	while (i < n)
	{
		// printf("iter in wait_process : %d\n", i);
		// printf("pids[%d] = %d\n", i, shell->exec->pids[i]);
		if (waitpid(shell->exec->pids[i], &status, 0) < 0)
			return (-1);
		i++;
	}
	free(shell->exec->pids);
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
