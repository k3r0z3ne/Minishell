/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:04:08 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/10 16:16:14 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>

typedef struct	s_SimpleCommand
{
	int		_numberOfArgs;
	char	**_commands;
}				t_SimpleCommand;

typedef struct	s_Command
{
	int		_numberOfSimpleCmds;
	bool	one_cmd;
	char	*_infile;
	char	*_outfile;
	char	*_errfile;
	t_SimpleCommand	*SimpleCommand;
}				t_Command;
typedef struct	s_shell
{
	char	**argv;
	char	**envp;
	int		infile;
	int		outfile;
	int		nb_cmd;
	int		**pipe;
	pid_t	*pids;
	t_Command	*commands;
}				t_shell;

/* minishell */
int	main(int argc, char **argv, char **envp);

/* init */
void	init_pipes(t_shell *shell);
void	init_shell(t_shell *shell, char **argv, char **envp);

/* builtins */

#endif