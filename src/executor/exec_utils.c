/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/17 13:55:12 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	prt_process(t_cmd *cmd, int i, int n)
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

void	redirect_setup(t_cmd *cmd, int i, int n)
{
	if (i == 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
			closerror(cmd, "dup2a");
		if (dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
			closerror(cmd, "dup2b");
		clear_pipe(cmd);
	}
	else if (i == n - 1)
	{
		if (dup2(cmd->pipe[0], STDIN_FILENO) < 0)
			closerror(cmd, "dup2c");
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
			closerror(cmd, "dup2d");
		clear_pipe(cmd);
	}
	else
	{
		if (dup2(cmd->pipe[0], STDIN_FILENO) < 0)
			closerror(cmd, "dup2e");
		if (dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
			closerror(cmd, "dup2f");
		clear_pipe(cmd);
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
			return ;
		i++;
	}
	// free(cmd->pids);
	return (status);
}

int	is_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (1);
	else
		return (0);
}
