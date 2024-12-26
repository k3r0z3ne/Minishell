/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/26 10:22:40 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	parent_process(t_cmd *cmd, int i, int n)
{
	if (i == 0)
	{
		close(cmd->infile);
		close(cmd->pipe[i]);
	}
	else if (i == n - 1)
	{
		close(cmd->outfile);
		close(cmd->pipe[i - 1]);
	}
	else
	{
		close(cmd->pipe[i - 1]);
		close(cmd->pipe[i]);
	}
}

int	wait_process(t_cmd *cmd, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
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
	// else if (!ft_strcmp(cmd->full_cmd[0], "export"))
	// 	shell->exit_status = ft_export();
	// else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
	// 	shell->exit_status = ft_unset();
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		shell->exit_status = ft_env(shell->envp);
	// else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	// 	shell->exit_status = ft_exit(shell->exit_status);
	else
		return (0);
	return (shell->exit_status);
}

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	// printf("cmd->next in count_cmd : %p\n", cmd->next);
	tmp = cmd;
	printf("cmd in count_cmd : %p\n", cmd);
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
