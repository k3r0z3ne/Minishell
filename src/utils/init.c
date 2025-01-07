/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:34:29 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/07 14:59:31 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->argc = argc;
	shell->exit_status = 0;
	shell->argv = argv;
	if (envp)
		shell->envp = envp;
	// else
	// 	shell->envp = ;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->clean = NULL;
}
