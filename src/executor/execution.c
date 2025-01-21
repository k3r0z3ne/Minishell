/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/21 17:58:02 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_cmd(t_shell *shell)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = find_path(shell);
	if (!tmp)
		return ;
	path = check_path(shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		path = NULL;
		path = ft_strdup(shell->cmd->full_cmd[0]);
	}
	if (!path)
		return ;
	// printf("EXECVE\n");6
	if (execve(path, shell->cmd->full_cmd, shell->envp) < 0)
	{
		free(path);
		// free_array(shell->cmd->full_cmd);
		return ;
	}
}

pid_t	process(t_shell *shell)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		return (-1);
	else if (ret == 0)
	{
		if (redirect_setup(shell->exec, shell->cmd->redirs) < 0)
			return (-1);
		exec_cmd(shell);
	}
	else
		parent_process(shell->exec, shell->cmd->redirs);
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;
	int	exit_status;

	shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * how_much_cmd(shell));
	if (!shell->exec->pids)
		return (-1);
	i = 0;
	exit_status = 0;
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		if (make_pipes(shell, i) < 0)
			return (-1);
		if (is_builtin(shell) == true)
		{
			exit_status = exec_builtin(shell);
			return (exit_status);
		}
		else
			shell->exec->pids[i] = process(shell);
		// printf("cmd : %s\n", shell->cmd->full_cmd[0]);
		// printf("i = %d\n", i);
		shell->cmd = shell->cmd->next;
		i++;
	}
	// i = -1;
	// while (++i < how_much_cmd(shell))
	// {
	// 	if (waitpid(shell->exec->pids[i], &exit_status, 0) < 0)
	// 		return (-1);
	// }
	// printf("END\n);
	exit_status = wait_process(shell, how_much_cmd(shell));
	return (exit_status);
}

pid_t	only_cmd(t_shell *shell)
{
	int		exit_status;

	exit_status = 0;
	shell->exec->pids = tracked_malloc(shell, sizeof(pid_t));
	if (!shell->exec->pids)
		return (-1);
	if (is_builtin(shell) == true)
	{
		exit_status = exec_builtin(shell);
		return (exit_status);
	}
	shell->exec->pids[0] = fork();
	if (shell->exec->pids[0] < 0)
		return (-1);
	else if (shell->exec->pids[0] == 0)
	{
		is_redir(shell->exec, shell->cmd);
		exec_cmd(shell);
	}
	else if (shell->exec->pids[0] > 0 && shell->cmd->flag_hd == false)
		exit_status = wait_process(shell, 1);
	return (exit_status);
}

int	main_exec(t_shell *shell)
{
	int	exit_status;
	int	nb_cmd;

	nb_cmd = count_cmd(shell->cmd);
	if (redirection_check(shell, shell->exec, shell->cmd->redirs) < 0)
		return (-1);
	if (nb_cmd > 1)
		exit_status = several_cmds(shell);
	else if (nb_cmd == 1)
		exit_status = only_cmd(shell);
	else
		return (-1);
	unlink(".tmp.txt");
	return (exit_status);
}
