/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:48:25 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/19 12:51:51 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, char **cmd)
{
	if (shell->exec->if_pipe == false)
	{
		if (!ft_strcmp(cmd[0], "exit") && !cmd[1])
		{
			fprintf(stderr, "%d\n", shell->last_status);
			cleanup_all(shell);
			free(shell->input);
			free_array(shell->envp);
			free(shell);
			exit(0);
		}
		if (!ft_strcmp(cmd[0], "exit") && !ft_strlen(cmd[1]))
			exit_err(shell);
		else if (cmd[1] && !cmd[2])
			exit_code(shell, cmd);
	}
	else if (cmd[1] && !cmd[2])
		exit_code_in_pipes(shell, cmd[1]);
}

void	exit_err(t_shell *shell)
{
	ft_putendl_fd("minishell: exit: : numeric argument required", 2);
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(2);
}

void	exit_code(t_shell *shell, char **args)
{
	int	code;

	if (!is_exit_correct(shell, args[1], 0))
		code = shell->last_status;
	else
	{
		code = 255;
		fprintf(stderr, "%d\n", shell->last_status);
		cleanup_all(shell);
		free(shell->input);
		free_array(shell->envp);
		free(shell);
		fprintf(stderr, "code = %d\n", code);
		exit(code);
	}
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

	code_str = ft_strdup_track(shell, arg);
	if (!code_str)
		err_exit(shell, "Memory allocation failed");
	if (!is_exit_correct(shell, arg, 0))
		shell->last_status = ft_atoi(code_str);
	else
		shell->last_status = 255;
	fprintf(stderr, "%d\n", shell->last_status);
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(shell->last_status);
}

int	is_exit_correct(t_shell *shell, char *arg, int i)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 0;
	if (arg[i] == '+')
		i++;
	if (arg[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		ret *= 10 + arg[i] - 48;
		if (ret > 255)
			ret %= 256;
		i++;
	}
	if (sign == -1)
		ret = 256 - ret;
	shell->last_status = ret;
	return (0);
}
