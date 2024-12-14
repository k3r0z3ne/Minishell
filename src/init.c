/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:34:29 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/14 15:16:07 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return ;
	shell->argc = argc;
	shell->argv = argv;
	if (envp)
		shell->envp = envp;
	// else
		// shell->envp = ;
	shell->input = NULL;
	shell->token = NULL;
}
