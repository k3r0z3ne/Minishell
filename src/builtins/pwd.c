/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:55:14 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/18 17:34:15 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_pwd(int argc)
{
	char	*curr_dir;

	if (argc != 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (-1);
	}
	curr_dir = malloc(sizeof(char) * 1024);
	if (!curr_dir)
		return (-1); 
	if (getcwd(curr_dir, 1024) == NULL)
	{
		free(curr_dir);
		return (-1);
	}
	ft_putendl_fd(curr_dir, 1);
	free(curr_dir);
	return (0);
}
