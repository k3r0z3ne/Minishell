/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/13 17:35:24 by arotondo         ###   ########.fr       */
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
	if (execve(path, cmd->full_cmd, shell->envp) < 0)
	{
		free(path);
		free_array(cmd->full_cmd);
		return ;
	}
}

pid_t	process(t_shell *shell, t_cmd *cmd, int i, int n)
{
	pid_t	ret;
	int		exit_status;

	exit_status = is_builtin(shell, cmd);
	if (!is_builtin(shell, cmd))
		return (exit_status);
	ret = fork();
	if (ret < 0)
		return (-1);
	else if (ret == 0)
	{
		redirect_setup(cmd, i, n);
		exec_cmd(shell, cmd);
	}
	else
		parent_process(cmd, i, n);
	return (ret);
}

int	several_cmds(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	exit_status;

	i = 0;
	cmd->pids = malloc(sizeof(pid_t) * how_much_cmd(shell));
	if (!cmd->pids)
		return (-1);
	while (cmd && i < shell->cmd_count)
	{
		if (make_pipes(shell, i) < 0)
			return (-1);
		if (is_builtin(shell, cmd))
			exit_status = is_builtin(shell, cmd);
		else
			cmd->pids[i] = process(shell, cmd, i, shell->cmd_count);
		if (cmd->is_pipe == true)
			free(shell->cmd->pipe);
		cmd = cmd->next;
		i++;
	}
	exit_status = wait_process(cmd, how_much_cmd(shell));
	return (exit_status);
}

pid_t	only_cmd(t_shell *shell, t_cmd *cmd)
{
	int	exit_status;

	exit_status = is_builtin(shell, cmd);
	if (!is_builtin(shell, cmd))
		return (exit_status);
	cmd->pids[0] = fork();
	if (cmd->pids[0] < 0)
		return (-1);
	else if (cmd->pids[0] == 0)
	{
		is_redir(cmd);
		exec_cmd(shell, cmd);
	}
	else if (cmd->pids[0] > 0 && cmd->flag_hd == false)
		exit_status = wait_process(cmd, 1);
	return (exit_status);
}

int	main_exec(t_shell *shell)
{
	int	exit_status;

	if (redirection_check(shell, shell->cmd, shell->cmd->redirs) < 0)
		return (-1);
	printf("nb cmd = %d\n", count_cmd(shell->cmd));
	if (count_cmd(shell->cmd) > 1)
		exit_status = several_cmds(shell, shell->cmd);
	else if (count_cmd(shell->cmd) == 1)
		exit_status = only_cmd(shell, shell->cmd);
	else
		return (-1);
	unlink(".tmp.txt");
	return (exit_status);
}
