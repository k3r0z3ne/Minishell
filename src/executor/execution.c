/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/30 16:54:54 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	char *path;
	char *tmp;

	path = NULL;
	tmp = find_path(shell);
	if (!tmp)
		return;
	path = check_path(cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		path = NULL;
		path = ft_strdup(cmd->full_cmd[0]);
	}
	if (!path)
		return;
	if (execve(path, cmd->full_cmd, shell->envp) < 0)
	{
		free(path);
		return;
	}
	free(path);
	free_array(cmd->full_cmd);
}

pid_t	only_cmd(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = is_builtin(shell, cmd);
	if (status != 0)
		return (status);
	cmd->pids[0] = fork();
	if (*cmd->pids < 0)
		return (-1);
	else if (*cmd->pids == 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
			return (-1);
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
			return (-1);
		exec_cmd(shell, cmd);
	}
	// else
	// 	status = wait_process(cmd, 1);
	return (*cmd->pids);
}

pid_t	process(t_shell *shell, t_cmd *cmd, int i, int n)
{
	is_builtin(shell, cmd);
	cmd->pids[0] = fork();
	if (cmd->pids[0] < 0)
		return (-1);
	else if (*cmd->pids == 0)
	{
		redirect_setup(cmd, i, n);
		exec_cmd(shell, cmd);
	}
	else
		parent_process(cmd, i, n);
	return (*cmd->pids);
}

int several_cmds(t_shell *shell, t_cmd *cmd)
{
	int i;
	int n_cmds;
	int status;

	i = 0;
	n_cmds = ft_lstsize((t_list *)cmd);
	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * n_cmds);
	if (!cmd->pids)
		return (-1);
	while (cmd && i < n_cmds)
	{
		cmd->pipe = (int *)malloc(sizeof(int) * 2);
		if (!cmd->pipe)
			return (-1);
		cmd->pids[i] = process(shell, cmd, i, n_cmds);
		free(cmd->pipe);
		cmd = cmd->next;
		i++;
	}
	status = wait_process(cmd, n_cmds);
	return (status);
}

int main_exec(t_shell *shell, t_cmd *cmd)
{
	int ret;

	redirection_check(cmd, cmd->redirs);
	if (count_cmd(cmd) > 1)
		ret = several_cmds(shell, cmd);
	else if (count_cmd(cmd) == 1)
		ret = only_cmd(shell, cmd);
	else
		return (-1);
	unlink(".tmp");
	return (ret);
}
