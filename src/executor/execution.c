/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/22 16:53:03 by arotondo         ###   ########.fr       */
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
