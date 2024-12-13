/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/13 14:58:20 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	only_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	ret;

	path = NULL;
	if (is_builtin(shell, cmd))
		exec_builtin(shell, cmd);
	// path = ;
}

int	main_exec(t_shell *shell, t_cmd *cmd)
{
	int	ret;

	if (cmd->next)
		ret = several_cmds(shell, cmd);
	else
		ret = only_cmd(shell, cmd);
	return (ret);
}
