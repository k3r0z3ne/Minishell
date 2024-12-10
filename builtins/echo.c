/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:42 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/10 17:54:33 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_flag(char *flag, int *i)
{
	if (flag == NULL)
		return (0);
	if (ft_strncmp(flag, "-n", 2) == 0)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_echo(int nb, char **arg, char **envp)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = check_flag(arg[1], &i);
	while (++i < nb)
	{
		j = 0;
		while (arg[i][j] && arg[i][j + 1])
		{
			if (arg[i][j] == '$' && ft_isupper(arg[i][++j]))
			{
				if (arg[i + 1] && ft_getenv(arg[++i], envp) == NULL)
					ft_putstr_fd("\n", 1);
			}
			else
				break ;
		}
		ft_putstr_fd(arg[i], 1);
		ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
