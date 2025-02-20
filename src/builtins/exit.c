/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:48:25 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/20 20:37:03 by xenon            ###   ########.fr       */
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
			fprintf(stderr, "%d\n", shell->last_status);
			code = shell->last_status;
			cleanup_all(shell);
			free(shell->input);
			free_array(shell->envp);
			free(shell);
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

void	exit_err(t_shell *shell)
{
	int	n;
	int	code;

	n = count_line(shell->cmd->full_cmd);
	if (is_exit_correct(shell, shell->cmd->full_cmd[1], 0))
	{
		code = 2;
		err_message(shell->cmd->full_cmd[0], shell->cmd->full_cmd[1], "numeric argument required");
	}
	else if (n > 2)
	{
		code = 1;
		shell->last_status = code;
		err_message(shell->cmd->full_cmd[0], NULL, "too many arguments");
		fprintf(stderr, "code = %d\n", code);
		return ;
	}
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	fprintf(stderr, "code = %d\n", code);
	exit(code);
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
	fprintf(stderr, "%d\n", code);
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(code);
}

int	test_max_min(char *arg)
{
	long	max;
	long	min;

	if (arg[0] == '-')
	{
		min = ft_atol(arg);
		if (min >= 0 && min <= LLONG_MAX)
			return (1);
	}
	else
	{
		max = ft_atol(arg);
		if (max <= 0 && max >= LLONG_MIN)
			return (1);
	}
	return (0);
}

int	is_exit_correct(t_shell *shell, char *arg, int i)
{
	long	ret;
	int		sign;

	ret = 0;
	sign = 0;
	if (test_max_min(arg))
		return (1);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[0] == '-')
		sign = -1;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		ret = (ret * 10) + arg[i] - 48;
		if (ret > 255)
			ret %= 256;
		i++;
	}
	if (sign == -1 && ret)
		ret = 256 - ret;
	shell->last_status = ret;
	return (0);
}
