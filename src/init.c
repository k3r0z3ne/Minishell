/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:34:29 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/16 12:28:32 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	// shell->argc = argc;
	// shell->argv = argv;
	if (envp)
		shell->envp = envp;
	// else
		// shell->envp = ;
	shell->input = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
}
