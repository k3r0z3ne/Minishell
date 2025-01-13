/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/13 17:37:45 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_process(t_cmd *cmd, int i, int n)
{
	if (i == 0)
	{
		close(cmd->infile);
		close(cmd->pipe[1]);
	}
	else if (i == n - 1)
	{
		close(cmd->pipe[0]);
		close(cmd->outfile);
	}
	else
	{
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
	}
}

int	make_pipes(t_shell *shell, int i)
{
	if (i < shell->cmd_count - 1)
	{
		shell->cmd->pipe = (int *)malloc(sizeof(int) * 2);
		if (!shell->cmd->pipe)
			return (-1);
		if (pipe(shell->cmd->pipe) < 0)
			return (-1);
		shell->cmd->is_pipe = true;
		return (0);
	}
	else
	{
		shell->cmd->is_pipe = false;
		return (0);
	}
}

int	wait_process(t_cmd *cmd, int n)
{
	int	i;
	int	status;

	i = 0;
	printf("max iter = %d\n", n);
	while (i < n)
	{
		printf("iter in wait_process : %d\n", i + 1);
		printf("pids[%d] = %d\n", i, cmd->pids[i]);
		if (waitpid(cmd->pids[i], &status, 0) < 0)
			return (-1);
		i++;
	}
	free(cmd->pids);
	return (status);
}

int	is_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		shell->exit_status = ft_echo(count_line(cmd->full_cmd), \
		cmd->full_cmd, shell->envp);
	// else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
	// 	shell->exit_status = ft_cd(cmd->full_cmd[1], shell->envp);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		shell->exit_status = ft_pwd(shell->argc);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		shell->exit_status = ft_export(shell);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		shell->exit_status = ft_unset(shell);
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		shell->exit_status = ft_env(shell->envp);
	// else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	// {
	// 	shell->exit_status = 0;
	// 	ft_exit(cmd->full_cmd, shell->exit_status);
	// }
	else
		return (-1);
	return (shell->exit_status);
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
