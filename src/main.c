/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2025/02/28 14:16:19 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

// static char	*my_readline(t_shell *shell, char *prompt)
// {
// 	(void)shell;
// 	// ssize_t	buf_len;
// 	// char	buffer[1024];
// 	char	*ret;

// 	ret = NULL;
// 	if (isatty(STDIN_FILENO))
// 	{
// 		ret = readline(prompt);
// 		fprintf(stderr, "readline\n");
// 	}
// 	// else
// 	// {
// 	// 	// fprintf(stderr, "HERE\n");
// 	// 	// buf_len = read(STDIN_FILENO, buffer, sizeof(buffer));
// 	// 	// if (buf_len < 0)
// 	// 	// 	return (NULL);
// 	// 	// while (buffer[buf_len] != '\n' || buffer[buf_len] != '\0')
// 	// 	// 	buf_len++;
// 	// 	// buffer[buf_len] = '\0';
// 	// 	// ret = ft_strdup_track(shell, buffer);
// 	// }
// 	fprintf(stderr, "ret\n");
// 	return (ret);
// }

// static char	*my_readline(char *prompt)
// {
// 	char	*ret;
// 	ssize_t	buf_len;

// 	ret = prompt;
// 	buf_len = 0;
// 	if (isatty(STDIN_FILENO) == 1)
// 		ret = readline(prompt);
// 	else
// 		buf_len = read(STDIN_FILENO, ret, 12);
// 	return (ret);
// }

static void	shell_main_loop(t_shell *shell)
{
	while (1)
	{
		setup_signals(shell);
		shell->input = readline("minishell> ");
		if (g_signal)
		{
			shell->last_status = 128 + g_signal;
			g_signal = 0;
		}
		if (!shell->input)
		{
			fprintf(stderr, "%d\n", shell->last_status);
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*shell->input != '\0')
			add_history(shell->input);
		shell->token = lexer(shell->input, shell);
		if (shell->token)
		{
			// print_tokens(shell->token);
			parser(shell);
			if (shell->cmd)
			{
				// print_table(shell->cmd);
				// print_redirs(shell->cmd);
				shell->last_status = main_exec(shell);
			}
		}
		cleanup_all(shell);
		free(shell->input);
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
