/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:42 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/10 16:32:08 by arotondo         ###   ########.fr       */
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
	flag = check_flag(arg[i], &i);
	while (++i < nb)
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '$')
			{
				if (getenv(arg[++i]) == NULL)
				{
					ft_putstr_fd("\n", 1);
					return (0);
				}
			}
			j++;
		}
		ft_putstr_fd(arg[i], 1);
		ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	ret;

	ret = ft_echo(argc, argv, envp);
	return (0);
}
