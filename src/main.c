/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:04:51 by witong            #+#    #+#             */
/*   Updated: 2024/12/30 16:53:39 by arotondo         ###   ########.fr       */
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
		// printf("shell->cmd before : %p\n", shell->cmd);
		shell->cmd = parser(shell, shell->token);
		// printf("shell->cmd after : %p\n", shell->cmd);
		shell->exit_status = main_exec(shell, shell->cmd);
		print_tokens(shell->token);
		print_table(shell->cmd);
		print_redirs(shell->cmd);
		free(shell->input);
	}
	rl_clear_history();
	return (0);
}
