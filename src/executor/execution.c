/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/31 17:13:28 by arotondo         ###   ########.fr       */
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
	if (path || path[0] == '\0')
	{
		perror("No command path found");
		exit(EXIT_FAILURE);
	}
	if (execve(path, shell->cmd->full_cmd, shell->envp) < 0)
		free(path);
}

int	main_exec(t_shell *shell)
{
	int	exit_status;

	shell->exec->cmd_count = count_cmd(shell->cmd);
	shell->exec->builtin_less = how_much_cmd(shell);
	if (shell->exec->cmd_count > 1)
		exit_status = several_cmds(shell);
	else if (shell->exec->cmd_count == 1)
		exit_status = only_cmd(shell);
	else
	{
		perror("No command found");
		exit(EXIT_FAILURE);
	}
	unlink(".tmp.txt");
	fprintf(stderr, "EOC\n");
	return (exit_status);
}
