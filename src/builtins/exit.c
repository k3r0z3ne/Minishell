/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:48:25 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/21 19:15:32 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, char **cmd)
{
	int	code;

	code = 0;
	if (!ft_strcmp(cmd[0], "exit") && !cmd[1])
	{
		code = shell->last_status;
		cleanup_all(shell);
		free(shell->input);
		free_array(shell->envp);
		free(shell);
		exit(code);
	}
	if (shell->exec->if_pipe == false)
	{
		if (count_line(cmd) > 2)
			exit_err(shell);
		else if (cmd[1] && !cmd[2])
			exit_code(shell, cmd);
	}
	else
		exit_code_in_pipes(shell, cmd);
}

void	exit_code(t_shell *shell, char **args)
{
	int	code;

	code = 0;
	if (!is_exit_correct(shell, args[1], 0))
		code = shell->last_status;
	else
		exit_err(shell);
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(code);
}

void	exit_code_in_pipes(t_shell *shell, char **arg)
{
	int	code;

	perror("here");
	code = 0;
	if (count_line(arg) > 2)
		exit_err(shell);
	else if (!is_exit_correct(shell, arg[1], 0))
		code = ft_atol(arg[1]);
	else
		exit_err(shell);
	code = shell->last_status;
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(code);
}
