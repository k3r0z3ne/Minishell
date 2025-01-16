/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2025/01/16 17:16:16 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, ac, av, envp);
	while (1)
	{
		shell->input = NULL;
		shell->input = readline("minishell> ");
		if (!shell->input)
			break ;
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
				shell->exec->exit_status = main_exec(shell);
			}
		}
		cleanup_all(shell);
	}
	free(shell);
	rl_clear_history();
	return (0);
}
