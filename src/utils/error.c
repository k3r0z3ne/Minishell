/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:05 by xenon             #+#    #+#             */
/*   Updated: 2025/02/19 18:43:00 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	err_exit(t_shell *shell, char *err_message)
{
	perror(err_message);
	cleanup_all(shell);
	free(shell->input);
	free_array(shell->envp);
	free(shell);
	exit(EXIT_FAILURE);
}

int	err_return(char *err_message)
{
	perror(err_message);
	return (1);
}

void	err_message(char *cmd, char *arg, char *mess)
{
	ft_putstr_fd("minishell: ", 2);
	write(2,  cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	ft_putstr_fd(arg, 2);
	write(2, ": ", 2);
	ft_putendl_fd(mess, 2);
}
