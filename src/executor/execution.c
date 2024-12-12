/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:23 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/10 14:00:03 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_SimpleCommand *command)
{
	
}

void	exec_several(t_Command *commands)
{
	
}

// changer les return
pid_t	process(t_shell *shell)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		return (1);
	else if (ret == 0)
		execute(shell->commands);
	else
		parent_proccess(shell);
	return (ret);
}

void	execute(t_Command *commands)
{
	if (commands->one_cmd == true)
		exec_simple(commands->SimpleCommand);
	else
		exec_several(commands);
}
