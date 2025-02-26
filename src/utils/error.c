/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:05 by xenon             #+#    #+#             */
/*   Updated: 2025/02/26 13:20:34 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

// int	err_exit(t_shell *shell)
// {
// 	cleanup_all(shell);
// 	free(shell->input);
// 	free_array(shell->envp);
// 	free(shell);
// 	exit(EXIT_FAILURE);
// }

void	err_message(t_shell *shell, char *cmd, char *arg, char *mess)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	if (!mess)
		perror("");
	else
		ft_putendl_fd(mess, 2);
	simple_exit(shell, shell->last_status);
}

void	err_message2(char *cmd, char *arg, char *mess)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	if (!mess)
		perror("");
	else
		ft_putendl_fd(mess, 2);
}
