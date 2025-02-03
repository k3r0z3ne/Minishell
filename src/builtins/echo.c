/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:42 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/03 15:51:32 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// en suspens : test avec append void test_echo.sh
// gerer le cas ./my_echo - aaa		-->	doit ecrire a partir de a

void	apply_flag(int flag)
{
	if (flag == 0)
		write(1, "\n", 1);
}

int	check_flag(char **flag, int *idx)
{
	int	i;
	int	j;

	i = 1;
	if (flag[i] == NULL)
		return (0);
	while (flag[i] && flag[i][0] == '-')
	{
		j = 1;
		while (flag[i][j] == 'n')
			j++;
		if (flag[i][j] == '\0')
		{
			(*idx)++;
			return (1);
		}
		(*idx)++;
		i++;
	}
	return (0);
}

int	ft_echo(int nb, char **arg, char **envp)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = check_flag(arg, &i);
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
		if (i != nb - 1)
			ft_putchar_fd(' ', 1);
	}
	apply_flag(flag);
	return (0);
}
