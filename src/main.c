/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2025/03/04 13:29:03 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	shell_main_process(t_shell *shell)
{
	shell->token = lexer(shell->input, shell);
	if (shell->token)
		parser(shell);
	if (shell->token && shell->cmd)
		shell->last_status = main_exec(shell);
	cleanup_all(shell);
	free(shell->input);
}

static void	shell_main_loop(t_shell *shell)
{
	while (1)
	{
		setup_signals(shell);
		if (isatty(STDIN_FILENO))
			shell->input = readline("minishell> ");
		else
			simple_exit2(shell, 1);
		if (g_signal)
		{
			shell->last_status = 128 + g_signal;
			g_signal = 0;
			free(shell->input);
			continue ;
		}
		if (!shell->input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*shell->input != '\0')
			add_history(shell->input);
		shell_main_process(shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, ac, av, envp);
	shell_main_loop(shell);
	free_array(shell->envp);
	free(shell);
	rl_clear_history();
	return (0);
}
