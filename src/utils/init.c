/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:34:29 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/18 16:36:07 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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
