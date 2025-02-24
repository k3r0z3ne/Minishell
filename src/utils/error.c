/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:05 by xenon             #+#    #+#             */
/*   Updated: 2025/02/24 16:51:09 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	err_exit(t_shell *shell, int code)
{
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(code);
}

void	err_message(char *cmd, char *arg, char *mess)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	ft_putendl_fd(mess, 2);
}
