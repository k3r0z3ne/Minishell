/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/22 16:41:42 by arotondo         ###   ########.fr       */
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
	{
		perror("$PATH not found");
		exit(EXIT_FAILURE);
	}
	path = check_path(shell->cmd->full_cmd, tmp);
	if (path && path[0] == '\0')
	{
		path = NULL;
		path = ft_strdup(shell->cmd->full_cmd[0]);
	}
	if (!path)
	{
		perror("No command path found");
		exit(EXIT_FAILURE);
	}
	// fprintf(stderr, "EXECVE\n");
	if (execve(path, shell->cmd->full_cmd, shell->envp) < 0)
	{
		free(path);
		// free_array(shell->cmd->full_cmd);
	}
}

pid_t	process(t_shell *shell, int i)
{
	int		old_pipe;
	pid_t	ret;

	old_pipe = -1;
	ret = fork();
	if (ret < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (ret == 0)
	{
		setup_old_pipe(shell->exec, i, old_pipe);
		redirect_setup(shell->exec, shell->cmd->redirs);
		exec_cmd(shell);
	}
	if (old_pipe != -1)
		close(old_pipe);
	if (i < shell->exec->cmd_count - 1)
	{
		close(shell->exec->pipe[1]);
		old_pipe = shell->exec->pipe[0];
	}
	// parent_process(shell->exec, shell->cmd->redirs);
	return (ret);
}

int	several_cmds(t_shell *shell)
{
	int	i;
	int	exit_status;

	shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * how_much_cmd(shell));
	if (!shell->exec->pids)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	exit_status = 0;
	while (shell->cmd && i < shell->exec->cmd_count)
	{
		shell->exec->last_cmd = (i == shell->exec->cmd_count - 1);
		make_pipes(shell, i);
		if (is_builtin(shell) == true)
		{
			exit_status = exec_builtin(shell);
			return (exit_status);
		}
		else
			shell->exec->pids[i] = process(shell, i);
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

int	main_exec(t_shell *shell)
{
	int	exit_status;
	int	nb_cmd;

	nb_cmd = count_cmd(shell->cmd);
	if (nb_cmd > 1)
		exit_status = several_cmds(shell);
	else if (nb_cmd == 1)
		exit_status = only_cmd(shell);
	else
	{
		perror("No command found");
		exit(EXIT_FAILURE);
	}
	unlink(".tmp.txt");
	return (exit_status);
}
