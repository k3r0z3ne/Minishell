/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/16 18:12:00 by arotondo         ###   ########.fr       */
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

int	parent_process(pid_t *pid)
{
	int	status;

	if (waitpid(*pid, &status, 0) < 0)
		return (-1); // appel fonction de free
	return (status);
}

pid_t	only_cmd(t_shell *shell, t_cmd *cmd)
{
	int		status;

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
		status = parent_process(cmd->pids);
	return (cmd->pids);
}

int	several_cmds(t_shell *shell, t_cmd *cmd)
{
	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * )
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
