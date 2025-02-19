/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:05 by xenon             #+#    #+#             */
/*   Updated: 2025/02/19 12:11:46 by witong           ###   ########.fr       */
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
