/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2025/01/07 00:49:05 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
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
		shell->token = lexer(shell->input);
		if (shell->token)
		{
			print_tokens(shell->token);
			parser(shell);
			if (shell->cmd)
			{
				print_table(shell->cmd);
				print_redirs(shell->cmd);
			//	shell->exit_status = main_exec(shell, shell->cmd);
			}
		}
		free_token(&shell->token);
		free_cmd(&shell->cmd);
	}
	rl_clear_history();
	return (0);
}
