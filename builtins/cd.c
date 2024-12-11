/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:37:27 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/11 12:32:52 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(const char *path, char **envp)
{
	char	*go_home;

	go_home = ft_getenv("HOME", envp);
	if (go_home == NULL)
		return (1);
	printf("%s\n", getcwd(go_home, ft_strlen(go_home)));
	chdir(go_home);
	// printf("%s\n", go_home);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	return (ft_cd(argv[1], envp));
}
