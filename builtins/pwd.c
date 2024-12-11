/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:55:14 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/10 18:08:52 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(int argc)
{
	char	*curr_dir;

	if (argc != 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	curr_dir = malloc(sizeof(char) * 1024);
	if (!curr_dir)
		return ; 
	if (getcwd(curr_dir, 1024) == NULL)
	{
		free(curr_dir);
		return ;
	}
	ft_putendl_fd(curr_dir, 1);
	free(curr_dir);
}
