/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:48:25 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/21 16:37:55 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, char **cmd)
{
	int	code;

	code = 0;
	if (shell->exec->if_pipe == false)
	{
		if (!ft_strcmp(cmd[0], "exit") && !cmd[1])
		{
			code = shell->last_status;
			cleanup_all(shell);
			free(shell->input);
			free_array(shell->envp);
			free(shell);
			fprintf(stderr, "%d\n", code);
			exit(code);
		}
		else if (count_line(cmd) > 2)
			exit_err(shell);
		else if (cmd[1] && !cmd[2])
			exit_code(shell, cmd);
	}
	else if (cmd[1] && !cmd[2])
		exit_code_in_pipes(shell, cmd[1]);
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
	fprintf(stderr, "code = %d\n", code);
	exit(code);
}

void	exit_code_in_pipes(t_shell *shell, char *arg)
{
	char	*code_str;
	int		code;

	code_str = ft_strdup_track(shell, arg);
	if (!code_str)
		err_exit(shell, "Memory allocation failed");
	if (!is_exit_correct(shell, arg, 0))
		code = ft_atoi(code_str);
	else
		code = 255;
	// fprintf(stderr, "%d\n", code);
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(code);
}
