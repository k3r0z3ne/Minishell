/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/17 12:36:50 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = find_path(shell);
	if (!tmp)
		return ;
	path = check_path(cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		path = NULL;
		path = ft_strdup(cmd->full_cmd[0]);
	}
	if (!path)
		return ;
	if (execve(path, cmd, shell->envp) < 0)
	{
		free(path);
		return ;
	}
	free(path);
	free_tab(cmd);
}

pid_t	only_cmd(t_shell *shell, t_cmd *cmd)
{
	int	status;

	if (is_builtin(shell, cmd))
		exec_builtin(shell, cmd);
	cmd->pids = fork();
	if (cmd->pids < 0)
		return (-1);
	else if (cmd->pids == 0)
	{
		redirect_setup(shell, cmd);
		exec_cmd(shell, cmd);
	}
	else
		status = wait_process(cmd->pids, 1);
	return (cmd->pids);
}

pid_t	process(t_shell *shell, t_cmd *cmd, int i)
{
	if (is_builtin(shell, cmd))
		exec_builtin(shell, cmd);
	cmd->pids = fork();
	if (cmd->pids < 0)
		return (-1);
	else if (cmd->pids == 0)
	{
		redirect_setup(shell, cmd, i);
		exec_cmd(shell, cmd);
	}
	else
		parent_process();
	return (cmd->pids);
}

int	several_cmds(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	n_cmds;
	int	status;

	i = 0;
	n_cmds = ft_lstsize(cmd);
	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * n_cmds);
	if (!cmd->pids)
		return (-1);
	
	while (i < n_cmds)
	{
		cmd->pipe = (int *)malloc(sizeof(int) * 2);
		if (!cmd->pipe)
			return ;
		cmd->pids[i] = process(shell, cmd, i);
		i++;
	}
	status = wait_process(cmd, n_cmds);
	return (status);
}

int	main_exec(t_shell *shell, t_cmd *cmd)
{
	int	ret;

	redirection_check(shell, cmd);
	if (cmd->next)
		ret = several_cmds(shell, cmd);
	else
		ret = only_cmd(shell, cmd);
	return (ret);
}
