/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:31 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/05 14:24:01 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

// renvoie 1 si ouvert et 0 si ferme ou invalide
int	is_fd_open(int fd)
{
	return (fcntl(fd, F_GETFD) != -1);
}

int	setup_old_pipe(t_shell *shell, t_exec *exec)
{
	if (exec->old_pipe != -1 && is_fd_open(exec->old_pipe))
	{
		if (dup2(exec->old_pipe, STDIN_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
		if (close(exec->old_pipe) < 0)
			err_message(shell, "close", NULL, NULL);
	}
	if (exec->last_cmd == false && exec->pipe[1] != 0)
	{
		perror("STEP2");
		if (dup2(exec->pipe[1], STDOUT_FILENO) < 0)
			err_message(shell, "redirection error", NULL, NULL);
		if (close(exec->pipe[1]) < 0)
			err_message(shell, "close", NULL, NULL);
		exec->pipe[1] = 0;
	}
	return (0);
}

static void	sig_handler(t_shell *shell, int *status, int *print_sigquit)
{
	int	signal;

	if (WIFEXITED(*status))
		shell->last_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		signal = WTERMSIG(*status);
		if (!(*print_sigquit) && signal == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			*print_sigquit = 1;
		}
		if (signal == SIGINT)
			write(2, "\n", 1);
		shell->last_status = 128 + signal;
	}
}

int	wait_process(t_shell *shell, int n)
{
	int	i;
	int	status;
	int	print_sigquit;

	if (!shell || !shell->exec || !shell->exec->pids)
		return (1);
	i = 0;
	status = 0;
	print_sigquit = 0;
	while (i < n)
	{
		if (shell->exec->pids[i] > 0)
		{
			perror("WAIT");
			if (waitpid(shell->exec->pids[i], &status, 0) < 0)
				err_message(shell, "waitpid", NULL, NULL);
			sig_handler(shell, &status, &print_sigquit);
		}
		i++;
	}
	return (shell->last_status);
}

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	if (!tmp || !tmp->full_cmd[0])
		return (0);
	i = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
