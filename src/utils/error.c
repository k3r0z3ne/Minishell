/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:05 by xenon             #+#    #+#             */
/*   Updated: 2025/03/02 21:47:16 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	close_pipes(t_shell *shell)
{
	if (shell->exec->last_cmd == false)
	{
		if (shell->exec->pipe[0])
			close(shell->exec->pipe[0]);
		if (shell->exec->pipe[1])
			close(shell->exec->pipe[1]);
	}
}

void	err_message(t_shell *shell, char *cmd, char *arg, char *mess)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	if (!mess)
		perror("");
	else
		ft_putendl_fd(mess, 2);
	if (shell->exec->cmd_count > 1)
		close_pipes(shell);
	tty_handler(shell);
	simple_exit(shell, shell->last_status);
}

void	err_message2(char *cmd, char *arg, char *mess)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	if (!mess)
		perror("");
	else
		ft_putendl_fd(mess, 2);
}
