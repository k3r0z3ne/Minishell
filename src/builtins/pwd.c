/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:55:14 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/03 16:01:25 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int argc)
{
	char	*curr_dir;

	if (argc != 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (-1);
	}
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (-1);
	ft_putendl_fd(curr_dir, 1);
	free(curr_dir);
	return (0);
}
